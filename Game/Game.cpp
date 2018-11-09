#include "Game.h"
#include <memory>
#include <functional>
#include <SFML/Graphics.hpp>

#include "BackgroundAbsoluteGrid.h"
#include "Button.h"
#include "SoundPack.h"

#include "SpriteFactory.h"

#include <iostream>

Game::Game()
{
	m_ManagedWindow = ManagedWindow::Create([]() {
		std::shared_ptr<sf::RenderWindow> Window = std::make_shared<sf::RenderWindow>();
		Window->create(sf::VideoMode(1000, 800), "HUNGER WARFARE 1 : WHO IS THE SURVIVOR");

		return Window;
	});

	// Test stage
	std::shared_ptr<BackgroundAbsoluteGrid> stage = BackgroundAbsoluteGrid::Create("pic/login/backLogin.jpg");
	m_ManagedWindow->AddChild(stage);

	// Button Sound
	std::shared_ptr<SoundPack> clickSound = SoundPack::FromFile("music/buttonPressed.wav");

	auto baseFrames = SpriteFactory::From("pic/menu/menu-sprite.png")
		->FrameSize(324, 78)->FrameCount(2);

	auto startBtnFrames = baseFrames->Clone()->FrameStartPosition(0, 0);
	auto startButton = MakeButton(clickSound, startBtnFrames);
	startButton->SetPosition(50, 50);

	auto rankBtnFrames = baseFrames->Clone()->FrameStartPosition(0, 78);
	auto rankButton = MakeButton(clickSound, rankBtnFrames);
	rankButton->SetPosition(50, 50*2 + 78);

	auto exitBtnFrames = baseFrames->Clone()->FrameStartPosition(0, 78*2);;
	auto exitButton = MakeButton(clickSound, rankBtnFrames);
	exitButton->SetPosition(50, 50*3 + 78*2);

	stage->AddChild(startButton);
	stage->AddChild(rankButton);
	stage->AddChild(exitButton);

	auto startClick = startButton->MouseClick->Then([](auto eventArgs) {
		std::cout << "Start clicked" << std::endl;
	});

	std::weak_ptr<ManagedWindow> weakWindow = m_ManagedWindow;
	auto exitClick = exitButton->MouseClick->Then([weakWindow](auto eventArgs) {
		auto shared = weakWindow.lock();
		if (shared) {
			shared->Terminate();
		}
	});

	m_ManagedWindow->Wait();

	while (m_ManagedWindow->IsValid()) {
		sf::sleep(sf::seconds(1));
	};
}

Game::~Game()
{
}

std::shared_ptr<Button> Game::MakeButton(std::shared_ptr<sf::Sound> clickSound, std::shared_ptr<SpriteFactory> btnFrames)
{
	auto btnNormal = btnFrames->Clone()
		->Then(Animation::Static(0))
		->Build()->GetModifier();

	auto btnHover = btnFrames->Clone()
		->Then(Animation::Static(1))
		->Build()->GetModifier();

	std::shared_ptr<Button> testBtn = Button::Create();
	testBtn->SetSize(324, 78);
	testBtn->SetClickSound(clickSound);
	testBtn->SetNormalSprite(btnNormal);
	testBtn->SetHoverSprite(btnHover);
	return testBtn;
}
