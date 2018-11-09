#pragma once
#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include <functional>
#include <vector>

#include "AnimationSprite.h"
#include "Animation.h"

class SpriteFactory final : public std::enable_shared_from_this<SpriteFactory>
{
	public:
		~SpriteFactory();

		std::shared_ptr<SpriteFactory> FrameStartPosition(float x, float y);
		std::shared_ptr<SpriteFactory> FrameSize(float width, float height);
		std::shared_ptr<SpriteFactory> FrameCount(int frameCount);
		std::shared_ptr<SpriteFactory> GameFramePerSpriteFrame(int period);

		std::shared_ptr<SpriteFactory> WithControl(std::shared_ptr<Control> control);

		std::shared_ptr<SpriteFactory> Then(AnimationSprite::CommandFunction command);

		std::shared_ptr<AnimationSprite> Build();

		static std::shared_ptr<SpriteFactory> From(std::string path);
		static std::shared_ptr<SpriteFactory> From(std::shared_ptr<sf::Texture> texture);

		static std::shared_ptr<AnimationSprite> Static(std::string path, std::shared_ptr<Control> control);
		static std::shared_ptr<AnimationSprite> Static(std::shared_ptr<sf::Texture> texture, std::shared_ptr<Control> control);

		std::shared_ptr<SpriteFactory> Clone();
	private:
		std::shared_ptr<sf::Texture> GetTexture();
		static std::shared_ptr<AnimationSprite> StaticBuilder(std::shared_ptr<SpriteFactory> factory, std::shared_ptr<Control> control);

		sf::Vector2f m_FrameStartPosition;
		sf::Vector2f m_FrameSize;
		int m_FrameCount = 1;
		int m_GameFramePerSpriteFrame = 1;

		std::shared_ptr<Control> m_BindedControl = nullptr;

		std::shared_ptr<std::vector<AnimationSprite::CommandFunction>> m_Commands;

		SpriteFactory(std::string path);
		SpriteFactory(std::shared_ptr<sf::Texture> texture);
		std::shared_ptr<sf::Texture> m_Texture = nullptr;
};

