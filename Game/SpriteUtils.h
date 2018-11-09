#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
#include "Control.h"

class AnimationSprite;

namespace SpriteUtils
{
	void InvertYSpriteWithTexture(sf::Sprite &sprite, sf::Texture &texture);

};
	
class SpriteControlModifier : public std::enable_shared_from_this<SpriteControlModifier> {
	public:
		bool IsSpriteValid();
		std::shared_ptr<AnimationSprite> GetSprite();

		std::shared_ptr<SpriteControlModifier> ResetAnimation();

		std::shared_ptr<SpriteControlModifier> InvertY();
		std::shared_ptr<SpriteControlModifier> DontInvertY();

		std::shared_ptr<SpriteControlModifier> Position(float x, float y);
		std::shared_ptr<SpriteControlModifier> Scale(float xScale, float yScale);

		std::shared_ptr<SpriteControlModifier> BindWithControl(std::shared_ptr<Control> control);

		static std::shared_ptr<SpriteControlModifier> For(std::shared_ptr<AnimationSprite> sprite);
		static std::shared_ptr<SpriteControlModifier> ForNull();

	protected:
		SpriteControlModifier(std::shared_ptr<AnimationSprite> sprite);

		virtual void ScaleSprite();

	private:
		std::unique_ptr<sf::Mutex> m_BuildMutex;

		std::shared_ptr<AnimationSprite> m_Sprite;
		std::shared_ptr<Control> m_Control;

		sf::Vector2f m_Scale = sf::Vector2f(1, 1);
		sf::Vector2f m_Position = sf::Vector2f(0, 0);
		bool m_DoInvertY = false;
};


