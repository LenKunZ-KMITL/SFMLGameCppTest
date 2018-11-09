#pragma once
#include "AbsoluteComponent.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>

#include "AnimationSprite.h"
#include "SpriteUtils.h"

class Button :
	public AbsoluteComponent
{
	public:
		~Button();

		void SetClickSound(std::shared_ptr<sf::Sound> sound);
		std::shared_ptr<sf::Sound> GetClickSound();
	
		static std::shared_ptr<Button> Create();

		void SetNormalSprite(std::shared_ptr<SpriteControlModifier> sprite);
		void SetHoverSprite(std::shared_ptr<SpriteControlModifier> sprite);

	protected:
		Button();

		virtual void RunDraw(sf::RenderTexture *canvas) override;

		virtual void RunTick(std::shared_ptr<TickState_t> state);
		virtual void RunMouseClickEvent(std::shared_ptr<MouseClickEventArgs_t> args);

	private:
		std::shared_ptr<sf::Sound> m_ClickSound = nullptr;

		std::shared_ptr<SpriteControlModifier> m_HoverModifier = nullptr;
		std::shared_ptr<SpriteControlModifier> m_NormalModifier = nullptr;
		std::shared_ptr<SpriteControlModifier> m_CurrentModifier = nullptr;
};

