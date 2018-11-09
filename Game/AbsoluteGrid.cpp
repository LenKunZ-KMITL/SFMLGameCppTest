#include <SFML/Graphics.hpp>

#include "AbsoluteGrid.h"

AbsoluteGrid::AbsoluteGrid()
{
	m_Childs = std::make_shared<std::set<std::shared_ptr<Control>>>();
	m_ChildMutex = std::make_unique<sf::Mutex>();
	Control::SetPosition(0, 0);
}

AbsoluteGrid::~AbsoluteGrid()
{
}

void AbsoluteGrid::AddChild(std::shared_ptr<Control> control)
{
	// Add and remove child will effect after current tick.
	sf::Lock Lock(*m_ChildMutex);
	if (m_NextTickChilds == nullptr) {
		m_NextTickChilds = CopyChilds();
	}
	m_NextTickChilds->insert(control);
	control->SetParent(shared_from_this());
}

void AbsoluteGrid::RemoveChild(std::shared_ptr<Control> control)
{
	// Add and remove child will effect after current tick.
	sf::Lock Lock(*m_ChildMutex);
	if (m_NextTickChilds == nullptr) {
		m_NextTickChilds = CopyChilds();
	}
	m_NextTickChilds->erase(control);
	control->RemoveParent(shared_from_this());
}

void AbsoluteGrid::RunDraw(sf::RenderTexture * canvas)
{
	Control::RunDraw(canvas);

	if (GetParent() != nullptr) {
		sf::Vector2f canvasSize = GetSize();
		sf::RenderTexture mainCanvas;
		mainCanvas.create((unsigned int)canvasSize.x, (unsigned int)canvasSize.y);
		mainCanvas.clear(sf::Color::Transparent);

		for (std::shared_ptr<Control> control : *m_Childs) {
			std::shared_ptr<sf::RenderTexture> childCanvas = std::make_shared<sf::RenderTexture>();
			sf::Vector2f controlSize = control->GetSize();

			childCanvas->create((unsigned int)controlSize.x, (unsigned int)controlSize.y);
			childCanvas->clear(sf::Color::Transparent);
			control->Draw(&*childCanvas);
			childCanvas->display();

			sf::Sprite childSprite(childCanvas->getTexture());
			childSprite.setPosition(control->GetPosition());

			mainCanvas.draw(childSprite);
		}
		mainCanvas.display();

		sf::Sprite mainSprite(mainCanvas.getTexture());
		mainSprite.setPosition(0, 0);
		canvas->draw(mainSprite);
	}
}

bool AbsoluteGrid::SetParent(std::shared_ptr<Control> parent)
{
	bool result = Control::SetParent(parent);

	// Always talk up full size
	Control::SetPosition(0, 0);
	return result;
}

bool AbsoluteGrid::RemoveParent(std::shared_ptr<Control> parent)
{
	bool result = Control::RemoveParent(parent);

	if (GetParent() == nullptr) {
		SetPosition(0, 0);
		SetSize(0, 0);
	}

	return result;
}

void AbsoluteGrid::SetPosition(float x, float y)
{
	throw "E_INVALIDOPERATION Absolute Grid must be at position (0, 0)";
}

sf::Vector2f AbsoluteGrid::GetSize()
{
	if (GetParent() != nullptr) {
		return GetParent()->GetSize();
	}
	else {
		return sf::Vector2f(0, 0);
	}
}

bool AbsoluteGrid::TakeFocus(Focusable * requester)
{
	if (Control::TakeFocus(requester)) {
		for (std::shared_ptr<Control> control : *m_Childs) {
			if (&*control != requester) {
				control->Blur();
			}
		}

		return true;
	}

	return false;
}

std::shared_ptr<AbsoluteGrid> AbsoluteGrid::Create()
{
	return std::shared_ptr<AbsoluteGrid>(new AbsoluteGrid());
}

void AbsoluteGrid::SetFocus()
{
	Control::SetFocus();
}

void AbsoluteGrid::RemoveFocus()
{
	Control::RemoveFocus();
	for (std::shared_ptr<Control> control : *m_Childs) {
		control->Blur();
	}
}

void AbsoluteGrid::RunTick(std::shared_ptr<TickState_t> state)
{
	Control::RunTick(state);

	// Before continue, apply add/remove effect.
	{
		sf::Lock Lock(*m_ChildMutex);
		if (m_NextTickChilds != nullptr) {
			m_Childs = m_NextTickChilds;
			m_NextTickChilds = nullptr;
		}
	}

	if (GetParent() != nullptr) {
		for (std::shared_ptr<Control> control : *m_Childs) {
			control->Tick(state);
		}
	}
}

std::shared_ptr<std::set<std::shared_ptr<Control>>> AbsoluteGrid::CopyChilds()
{
	return std::make_shared<std::set<std::shared_ptr<Control>>>(*m_Childs);
}
