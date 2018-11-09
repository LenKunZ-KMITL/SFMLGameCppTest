#include "Button.h"

Button::Button()
{
	m_CurrentModifier = SpriteControlModifier::ForNull();
	m_NormalModifier = SpriteControlModifier::ForNull();
	m_HoverModifier = SpriteControlModifier::ForNull();
}

Button::~Button()
{
}

void Button::RunDraw(sf::RenderTexture * canvas)
{
	if (m_CurrentModifier->IsSpriteValid()) {
		canvas->draw(*m_CurrentModifier->GetSprite());
	}
	else {
		sf::RectangleShape shape;
		shape.setSize(GetSize());
		shape.setFillColor(sf::Color::Red);
		shape.setPosition(0, 0);

		canvas->draw(shape);
	}
}

void Button::SetClickSound(std::shared_ptr<sf::Sound> sound)
{
	m_ClickSound = sound;
}

std::shared_ptr<sf::Sound> Button::GetClickSound()
{
	return m_ClickSound;
}

std::shared_ptr<Button> Button::Create()
{
	return std::shared_ptr<Button>(new Button());
}

void Button::SetNormalSprite(std::shared_ptr<SpriteControlModifier> sprite)
{
	m_NormalModifier = sprite->BindWithControl(shared_from_this());
}

void Button::SetHoverSprite(std::shared_ptr<SpriteControlModifier> sprite)
{
	m_HoverModifier = sprite->BindWithControl(shared_from_this());
}

void Button::RunTick(std::shared_ptr<TickState_t> state)
{
	Control::RunTick(state);

	if (state->MouseInBound 
		&& m_HoverModifier->IsSpriteValid()) 
	{
		if (m_HoverModifier != m_CurrentModifier) {
			m_CurrentModifier = m_HoverModifier->ResetAnimation();
		}
	}
	else if (m_NormalModifier->IsSpriteValid()) 
	{
		if (m_NormalModifier != m_CurrentModifier) {
			m_CurrentModifier = m_NormalModifier->ResetAnimation();
		}
	}
	else if (m_CurrentModifier->IsSpriteValid()){
		m_CurrentModifier = SpriteControlModifier::ForNull();
	}
}

void Button::RunMouseClickEvent(std::shared_ptr<MouseClickEventArgs_t> args)
{
	if (GetClickSound() != nullptr) {
		GetClickSound()->play();
	}

	Control::RunMouseClickEvent(args);
}
