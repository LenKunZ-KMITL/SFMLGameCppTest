#include "SpriteFactory.h"

SpriteFactory::SpriteFactory(std::string path)
{
	m_Texture = std::make_shared<sf::Texture>();
	m_Texture->loadFromFile(path);

	m_Commands = std::make_shared<std::vector<AnimationSprite::CommandFunction>>();
}

SpriteFactory::SpriteFactory(std::shared_ptr<sf::Texture> texture)
{
	m_Texture = texture;
	m_Commands = std::make_shared<std::vector<AnimationSprite::CommandFunction>>();
}

SpriteFactory::~SpriteFactory()
{
}

std::shared_ptr<SpriteFactory> SpriteFactory::FrameStartPosition(float x, float y)
{
	m_FrameStartPosition = sf::Vector2f(x, y);
	return shared_from_this();
}

std::shared_ptr<SpriteFactory> SpriteFactory::FrameSize(float width, float height)
{
	m_FrameSize = sf::Vector2f(width, height);
	return shared_from_this();
}

std::shared_ptr<SpriteFactory> SpriteFactory::FrameCount(int frameCount)
{
	if (frameCount < 1) {
		throw "E_OUTOFRANGE frameCount can't be less than 1";
	}

	m_FrameCount = frameCount;
	return shared_from_this();
}

std::shared_ptr<SpriteFactory> SpriteFactory::GameFramePerSpriteFrame(int period)
{
	if (period < 1) {
		throw "E_OUTOFRANGE period can't be less than 1.";
	}

	m_GameFramePerSpriteFrame = period;

	return shared_from_this();
}

std::shared_ptr<SpriteFactory> SpriteFactory::WithControl(std::shared_ptr<Control> control)
{
	m_BindedControl = control;
	return shared_from_this();
}

std::shared_ptr<SpriteFactory> SpriteFactory::Then(AnimationSprite::CommandFunction command)
{
	m_Commands->push_back(command);
	return shared_from_this();
}

std::shared_ptr<AnimationSprite> SpriteFactory::Build()
{
	auto sprite = std::shared_ptr<AnimationSprite>(new AnimationSprite(
		m_FrameStartPosition,
		m_FrameSize,
		m_FrameCount,
		m_GameFramePerSpriteFrame,
		m_Texture,
		m_Commands
	));

	if (m_BindedControl != nullptr) {
		sprite->DrawWithControl(m_BindedControl);
	}

	return sprite;
}

std::shared_ptr<SpriteFactory> SpriteFactory::From(std::string path)
{
	std::shared_ptr<SpriteFactory> factory = std::shared_ptr<SpriteFactory>(new SpriteFactory(
		path
	));
	return factory;
}

std::shared_ptr<SpriteFactory> SpriteFactory::From(std::shared_ptr<sf::Texture> texture)
{
	return std::shared_ptr<SpriteFactory>(new SpriteFactory(
		texture
	))->FrameStartPosition(0, 0)
		->FrameCount(1)
		->FrameSize((float)texture->getSize().x, (float)texture->getSize().y);
}

std::shared_ptr<AnimationSprite> SpriteFactory::Static(std::string path, std::shared_ptr<Control> control)
{
	auto factory = From(path);
	return StaticBuilder(factory, control);
}

std::shared_ptr<AnimationSprite> SpriteFactory::Static(std::shared_ptr<sf::Texture> texture, std::shared_ptr<Control> control)
{
	std::shared_ptr<SpriteFactory> factory = From(texture);
	return StaticBuilder(factory, control);
}

std::shared_ptr<SpriteFactory> SpriteFactory::Clone()
{
	std::shared_ptr<SpriteFactory> factory = std::shared_ptr<SpriteFactory>(new SpriteFactory(*shared_from_this()));
	factory->m_Commands = std::make_shared<std::vector<AnimationSprite::CommandFunction>>();
	return factory;
}

std::shared_ptr<sf::Texture> SpriteFactory::GetTexture()
{
	return m_Texture;
}

std::shared_ptr<AnimationSprite> SpriteFactory::StaticBuilder(std::shared_ptr<SpriteFactory> factory, std::shared_ptr<Control> control)
{
	auto size = factory->GetTexture()->getSize();
	return factory
		->FrameSize((float)size.x, (float)size.y)
		->FrameStartPosition(0, 0)
		->FrameCount(1)
		->GameFramePerSpriteFrame(1)
		->Then(Animation::Once())
		->WithControl(control)
		->Build();
}
