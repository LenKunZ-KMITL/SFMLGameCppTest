#pragma once
#include <functional>
#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>

#include "AnimationSpriteFinishEvent.h"
#include "Control.h"

class SpriteControlModifier;

class AnimationSprite: public sf::Sprite, public std::enable_shared_from_this<AnimationSprite>
{
	public:
		typedef std::function<void(std::shared_ptr<AnimationSprite>)> CommandFunction;

		std::unique_ptr<AnimationSpriteFinishEvent> SpriteReset;

		AnimationSprite(
			sf::Vector2f frameStartPosition,
			sf::Vector2f frameSize,
			int frameCount,
			int framePeriod,
			std::shared_ptr<sf::Texture> texture,
			std::shared_ptr<std::vector<CommandFunction>> commands
		);
		~AnimationSprite();

		void DrawWithControl(std::shared_ptr<Control> control);

		void NextCommand();
		void Reset();
		void End();
		bool CountDelay();

		void SendEndedFinishSignal();
		void SendContinuousFinishSignal();
		void SendFinishSignal(std::shared_ptr<AnimationSpriteFinishEventArgs> args);

		bool IsTerminated();
		bool NextFrame();

		bool RunNext();

		void SetCurrentFrameIndex(int frameIndex);
		int GetCurrentFrameIndex();

		int GetFrameCount();

		std::shared_ptr<SpriteControlModifier> GetModifier();

	private:
		void SetTexture(std::shared_ptr<sf::Texture> texture);

		void SetFrameStartPosition(sf::Vector2f startPosition);
		void SetFrameSize(sf::Vector2f frameSize);
		void SetFramePeriod(int period);
		void SetFrameCount(int frameCount);

		void ApplyTextureRect();

		std::unique_ptr<sf::Mutex> m_AnimationMutex;

		sf::Vector2f m_FrameStartPosition;
		sf::Vector2f m_FrameSize;
		int m_FrameCount;
		int m_FramePeriod;

		std::shared_ptr<sf::Texture> m_Texture = nullptr;
		int m_CurrentFrameIndex;
		sf::IntRect m_TextureRect;

		std::shared_ptr<std::vector<CommandFunction>> m_Commands = nullptr;
		int m_CurrentCommandIndex = 0;
		int m_DelayCount = 0;

		bool m_IsTerminated = false;

		std::weak_ptr<Control> m_CurrentBindedControl;
		ControlDrawEvent::SharedPtrFunction m_BindedFunction = nullptr;
};

