#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "ManagedWindow.h"
#include "Button.h"
#include "SpriteFactory.h"

class Game
{
	public:
		Game();
		~Game();

	private:
		std::shared_ptr<Button> MakeButton(std::shared_ptr<sf::Sound> clickSound, std::shared_ptr<SpriteFactory> btnFrames);

		std::shared_ptr<sf::RenderWindow> m_Window;
		std::shared_ptr<ManagedWindow> m_ManagedWindow;
};

