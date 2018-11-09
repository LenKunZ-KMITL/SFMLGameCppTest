#include "ManagedWindow.h"

#include <memory>
#include <vector>
#include <set>
#include <functional>


ManagedWindow::ManagedWindow(std::function<std::shared_ptr<sf::RenderWindow>()> creator) {
    m_Creator = creator;
    m_Controls = std::make_unique<std::set<std::shared_ptr<Control>>>();

	Control::SetParent(nullptr);

    SetFramerate(DEFAULT_FRAMERATE);
    SetTickrate(DEFAULT_TICKRATE);

    m_FrameClock = std::make_unique<sf::Clock>();
    m_TickClock = std::make_unique<sf::Clock>();

	m_FrameMutex = std::make_unique<sf::Mutex>();
	m_TickMutex = std::make_unique<sf::Mutex>();
	m_StartMutex = std::make_unique<sf::Mutex>();

	Start();
}

void ManagedWindow::InitThreads() {
	m_TickThread = std::make_unique<sf::Thread>(&ManagedWindow::TickThread, this);
	m_TickThread->launch();

	m_FrameThread = std::make_unique<sf::Thread>(&ManagedWindow::FrameThread, this);
	m_FrameThread->launch();
}

void ManagedWindow::FrameThread() {
	while (m_Parent == nullptr) {
		sf::sleep(sf::microseconds(1));
	}

	m_Parent->setActive(true);

	sf::Vector2u windowSize = m_Parent->getSize();
	sf::RenderTexture renderTexture;
	renderTexture.create(windowSize.x, windowSize.y);

	while (m_Parent->isOpen() && !m_Terminated) {
		if (!FrameThreadEnabled) {
			sf::sleep(sf::microseconds(1));
			continue;
		}

		sf::Lock Lock(*m_FrameMutex);
		if (m_FrameClock->getElapsedTime().asMicroseconds() > m_FramePeriodMicroseconds) {
			m_FrameClock->restart();

			// Prepare the texture to draw.

			renderTexture.clear();
			RunDraw(&renderTexture);
			renderTexture.display();

			sf::Sprite renderSprite(renderTexture.getTexture());

			m_Parent->draw(renderSprite);
			m_Parent->display();
		}
		else if (m_FramePeriodMicroseconds - m_FrameClock->getElapsedTime().asMicroseconds() > 500) {
			sf::sleep(sf::microseconds(m_FramePeriodMicroseconds - 500) - m_FrameClock->getElapsedTime());
		}
	}
}

void ManagedWindow::TickThread() {
	std::vector<sf::Event> eventDatas;
	std::shared_ptr<TickState_t> tickState = std::make_shared<TickState_t>();

	if (m_Parent == nullptr) {
		m_Parent = m_Creator();
		m_Parent->setActive(false);
	}

	while (m_Parent->isOpen() && !m_Terminated) {
		if (!TickThreadEnabled) {
			sf::sleep(sf::microseconds(1));
			continue;
		}

		// Poll all event
		sf::Event currentEvent;
		while (m_Parent->pollEvent(currentEvent)) {
			if (currentEvent.type == sf::Event::Closed) {
				m_Parent->close();
			}

			if (currentEvent.type == sf::Event::KeyPressed) {
				if (currentEvent.key.code == sf::Keyboard::Tab) {
					tickState->IsTab = true;
				}
			}

			eventDatas.push_back(currentEvent);
		}

		sf::Lock Lock(*m_TickMutex);
		if (m_TickClock->getElapsedTime().asMicroseconds() > m_TickPeriodMicroseconds) {
			std::set<sf::Event*> events;
			m_TickClock->restart();

			for (std::vector<sf::Event>::iterator it = eventDatas.begin(); it != eventDatas.end(); ++it) {
				events.insert(&*it);
			}

			sf::Vector2i mousePosition = sf::Mouse::getPosition(*m_Parent);

			tickState->Events = events;
			tickState->MousePosition = sf::Vector2f((float)mousePosition.x, (float)mousePosition.y);

			Tick(tickState);

			tickState = std::make_shared<TickState_t>();
			eventDatas.clear();
		}

		sf::sleep(sf::microseconds(m_TickPeriodMicroseconds / 2));
	}
}

void ManagedWindow::RunTick(std::shared_ptr<TickState_t> tickState) {
	Control::RunTick(tickState);

	for (std::shared_ptr<Control> control : *m_Controls) {
		control->Tick(tickState);
	}
}

void ManagedWindow::RunDraw(sf::RenderTexture *canvas) {
	Control::RunDraw(canvas);

	for (std::shared_ptr<Control> control : *m_Controls) {
		control->Draw(canvas);
	}
}

ManagedWindow::~ManagedWindow() {
	Terminate();
}

void ManagedWindow::AddChild(std::shared_ptr<Control> control) {
    m_Controls->insert(control);
    control->SetParent(shared_from_this());
}

void ManagedWindow::RemoveChild(std::shared_ptr<Control> control) {
    m_Controls->erase(control);
    control->RemoveParent(shared_from_this());
}

void ManagedWindow::SetFramerate(long framerate) {
    if(framerate < 1) {
        throw "E_OUTOFRANGE framerate can't be less than 1";
    }

    // Calculate frame period.
    double secondFraction = 1.0 / framerate;
    m_FramePeriodMicroseconds = (int64_t)(secondFraction * 1000000);

    m_Framerate = framerate;
}

long ManagedWindow::GetFramerate() {
    return m_Framerate;
}

void ManagedWindow::SetTickrate(long tickrate) {
    if(tickrate < 1) {
        throw "E_OUTOFRANGE tickrate can't be less than 1";
    }

    // Calculate tick period.
    double secondFraction = 1.0 / tickrate;
    m_TickPeriodMicroseconds = (int64_t) (secondFraction * 1000000);

    m_Tickrate = tickrate;
}

long ManagedWindow::GetTickrate() {
    return m_Tickrate;
}

bool ManagedWindow::IsValid()
{
	if (m_Parent == nullptr) {
		return true;
	}

	return m_Started && m_Parent->isOpen() && !m_Terminated;
}

void ManagedWindow::Terminate()
{
	m_Terminated = true;

	m_FrameThread->terminate();
	m_TickThread->terminate();
}

void ManagedWindow::Start()
{
	sf::Lock Lock(*m_StartMutex);
	if (!m_Started) {
		InitThreads();
		m_Started = true;
	}
}

std::shared_ptr<ManagedWindow> ManagedWindow::Create(std::function<std::shared_ptr<sf::RenderWindow>()> creator)
{
	return std::shared_ptr<ManagedWindow>(new ManagedWindow(creator));
}

sf::Vector2f ManagedWindow::GetSize()
{
	sf::Vector2u size = m_Parent->getSize();
	return sf::Vector2f((float)size.x, (float)size.y);
}

void ManagedWindow::Wait()
{
	m_FrameThread->wait();
	m_TickThread->wait();
}
