#include "SpriteUtils.h"
#include "AnimationSprite.h"

void SpriteUtils::InvertYSpriteWithTexture(sf::Sprite & sprite, sf::Texture & texture)
{
	sprite.setScale(1, -1);
	sprite.setPosition(0, (float)texture.getSize().y);
}

bool SpriteControlModifier::IsSpriteValid()
{
	return m_Sprite != nullptr;
}

std::shared_ptr<AnimationSprite> SpriteControlModifier::GetSprite()
{
	sf::Lock Lock(*m_BuildMutex);

	if (m_Sprite == nullptr) {
		throw "E_NULLPOINTER sprite is empty here.";
	}

	ScaleSprite();
	return m_Sprite;
}

std::shared_ptr<SpriteControlModifier> SpriteControlModifier::ResetAnimation()
{
	if (m_Sprite != nullptr) {
		m_Sprite->Reset();
	}

	return shared_from_this();
}

std::shared_ptr<SpriteControlModifier> SpriteControlModifier::InvertY()
{
	m_DoInvertY = false;
	return shared_from_this();
}

std::shared_ptr<SpriteControlModifier> SpriteControlModifier::DontInvertY()
{
	m_DoInvertY = false;
	return shared_from_this();
}

std::shared_ptr<SpriteControlModifier> SpriteControlModifier::Position(float x, float y)
{
	m_Position.x = x;
	m_Position.y = y;
	return shared_from_this();
}

std::shared_ptr<SpriteControlModifier> SpriteControlModifier::Scale(float xScale, float yScale)
{
	m_Scale.x = xScale;
	m_Scale.y = yScale;
	return shared_from_this();
}

std::shared_ptr<SpriteControlModifier> SpriteControlModifier::BindWithControl(std::shared_ptr<Control> control)
{
	if (control == nullptr) {
		throw "E_NULLPOINTER control can't be null";
	}

	m_Sprite->DrawWithControl(control);
	m_Control = control;
	return shared_from_this();
}

std::shared_ptr<SpriteControlModifier> SpriteControlModifier::For(std::shared_ptr<AnimationSprite> sprite)
{
	return std::shared_ptr<SpriteControlModifier>(new SpriteControlModifier(sprite));
}

std::shared_ptr<SpriteControlModifier> SpriteControlModifier::ForNull()
{
	return std::shared_ptr<SpriteControlModifier>(new SpriteControlModifier(nullptr));
}

SpriteControlModifier::SpriteControlModifier(std::shared_ptr<AnimationSprite> sprite)
{
	m_BuildMutex = std::make_unique<sf::Mutex>();

	if (sprite != nullptr) {
		m_Sprite = sprite;

		m_Position = sprite->getPosition();
	}
}

void SpriteControlModifier::ScaleSprite()
{
	sf::Vector2f size = m_Control->GetSize();
	sf::IntRect textureSize = m_Sprite->getTextureRect();

	float ratio;
	if (size.x < size.y) {
		ratio = size.x / (float)textureSize.width;
	}
	else {
		ratio = size.y / (float)textureSize.height;
	}

	if (m_DoInvertY) {
		m_Sprite->setScale(sf::Vector2f(m_Scale.x * ratio, -m_Scale.y * ratio));
		m_Sprite->setPosition(m_Position.x, m_Position.y + textureSize.height);
	}
	else {
		m_Sprite->setScale(sf::Vector2f(m_Scale.x * ratio, m_Scale.y * ratio));
		m_Sprite->setPosition(m_Position.x, m_Position.y);
	}
}
