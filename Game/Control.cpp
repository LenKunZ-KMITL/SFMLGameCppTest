#include "Control.h"
#include "PositionUtils.h"
#include <set>

Control::Control()
{
	MouseClick = std::make_unique<MouseClickEvent>();
	WhenDraw = std::make_unique<ControlDrawEvent>();

	m_ControlParentMutex = std::make_unique<sf::Mutex>();
	m_DrawMutex = std::make_unique<sf::Mutex>();
}

Control::~Control()
{
}

std::shared_ptr<Control> Control::GetSharedPtr()
{
	return shared_from_this();
}

void Control::Draw(sf::RenderTexture *canvas)
{
	sf::Lock Lock(*m_DrawMutex);

	WhenDraw->Emit(std::make_shared<ControlDrawEventArgs>());
	RunDraw(canvas);
}

void Control::Tick(std::shared_ptr<TickState_t> state)
{
	std::set<sf::Event*> unwantedEvents;
	bool parentMouseInBound = state->MouseInBound;

	sf::Vector2f mousePosition = state->MousePosition;
	sf::Vector2f controlAbsolutePosition = GetAbsolutePosition();

	if (parentMouseInBound) {
		state->MouseInBound = PositionUtils::IsPositionInBound(mousePosition, controlAbsolutePosition, GetSize());
	}

	for (sf::Event *event : state->Events) {
		// Mouse click
		if (event->type == sf::Event::MouseButtonPressed) {
			// For decompilcate things sake. Let's control handle mouse click position filter.

			if (state->MouseInBound) {
				std::shared_ptr<MouseClickEventArgs_t> eventArg = std::make_shared<MouseClickEventArgs_t>();
				eventArg->AbsolutePosition = mousePosition;
				eventArg->Position = PositionUtils::GetRelativePosition(controlAbsolutePosition, mousePosition);
				eventArg->Button = event->mouseButton.button;

				RunMouseClickEvent(eventArg);
			}
			else 
			{
				// If event not in bound, it will not be pass into child.
				unwantedEvents.insert(event);
			}
		}
	}

	// Remove unwantedEvents before call tick.
	for (sf::Event* event : unwantedEvents) {
		state->Events.erase(event);
	}

	RunTick(state);

	for (sf::Event* event : unwantedEvents) {
		state->Events.insert(event);
	}

	state->MouseInBound = parentMouseInBound;

	// User can also process mouse event.
	// But override RunMouseClickEvent will also allow interruption of MouseClickEvent triggering.
}

bool Control::SetParent(std::shared_ptr<Control> parent)
{
	sf::Lock Lock(*m_ControlParentMutex);

	if (m_ControlParent == parent) {
		return false;
	}

	m_NextControlParent = parent;
	return true;
}

bool Control::RemoveParent(std::shared_ptr<Control> parent)
{
	sf::Lock Lock(*m_ControlParentMutex);

	bool result = m_ControlParent == parent;
	if (m_ControlParent == parent) {
		m_NextControlParent == nullptr;
	}

	return result;
}

bool Control::HasNextParent()
{
	return m_NextControlParent != nullptr;
}

std::shared_ptr<Control> Control::GetParent()
{
	return m_ControlParent;
}

void Control::SetPosition(float x, float y)
{
	m_X = x;
	m_Y = y;
}

void Control::SetSize(float width, float height)
{
	m_Width = width;
	m_Height = height;
}

sf::Vector2f Control::GetPosition()
{
	return sf::Vector2f(m_X, m_Y);
}

sf::Vector2f Control::GetAbsolutePosition()
{
	sf::Vector2f position = GetPosition();
	float x = position.x, y = position.y;

	std::shared_ptr<Control> parent = GetParent();
	if (parent != nullptr) {
		sf::Vector2f parentAbsolutePosition = parent->GetAbsolutePosition();
		x += parentAbsolutePosition.x;
		y += parentAbsolutePosition.y;
	}

	return sf::Vector2f(x, y);
}

sf::Vector2f Control::GetSize()
{
	return sf::Vector2f(m_Width, m_Height);
}

bool Control::IsFocus()
{
	return m_Focusing;
}

void Control::Focus()
{
	if (m_ControlParent != nullptr) {
		if (m_ControlParent->TakeFocus(this)) {
			SetFocus();
		}
	}
}

void Control::Blur()
{
	RemoveFocus();
}

bool Control::TakeFocus(Focusable * requester)
{
	if (m_ControlParent != nullptr) {
		return m_ControlParent->TakeFocus(this);
	}
	else {
		return true;
	}
}

std::shared_ptr<Control> Control::Create()
{
	return std::shared_ptr<Control>(new Control());
}

void Control::RunTick(std::shared_ptr<TickState_t> state)
{
	{
		sf::Lock Lock(*m_ControlParentMutex);

		if (HasNextParent()) {
			m_ControlParent = m_NextControlParent;
			m_NextControlParent = nullptr;
		}
	}

	MouseClick->Tick();
	WhenDraw->Tick();
}

void Control::RunDraw(sf::RenderTexture * canvas)
{
}

void Control::RunMouseClickEvent(std::shared_ptr<MouseClickEventArgs_t> args)
{
	MouseClick->Emit(args);
}

void Control::SetFocus()
{
	m_Focusing = true;
}

void Control::RemoveFocus()
{
	m_Focusing = false;
}
