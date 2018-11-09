#include "BackgroundAbsoluteGrid.h"
#include <memory>

#include "SpriteUtils.h"
#include "SpriteFactory.h"

BackgroundAbsoluteGrid::BackgroundAbsoluteGrid() : AbsoluteGrid()
{
}

BackgroundAbsoluteGrid::~BackgroundAbsoluteGrid()
{
}

void BackgroundAbsoluteGrid::RunDraw(sf::RenderTexture* canvas)
{
	if (m_BackgroundSprite == nullptr) {
		return;
	}

	canvas->draw(*m_BackgroundSprite->GetSprite());

	AbsoluteGrid::RunDraw(canvas);
}

void BackgroundAbsoluteGrid::SetBackground(std::string backgroundPath)
{
	auto backgroundSprite = SpriteFactory::Static(backgroundPath, shared_from_this());

	m_BackgroundSprite = backgroundSprite->GetModifier()
		->Position(0, 0)
		->Scale(1, 1)
		->InvertY();
}

void BackgroundAbsoluteGrid::RemoveBackground(std::string backgroundPath)
{
	m_BackgroundSprite = SpriteControlModifier::ForNull();
}

bool BackgroundAbsoluteGrid::SetParent(std::shared_ptr<Control> parent)
{
	return AbsoluteGrid::SetParent(parent);
}

bool BackgroundAbsoluteGrid::RemoveParent(std::shared_ptr<Control> parent)
{
	return AbsoluteGrid::RemoveParent(parent);
}

std::shared_ptr<BackgroundAbsoluteGrid> BackgroundAbsoluteGrid::Create()
{
	return std::shared_ptr<BackgroundAbsoluteGrid>(new BackgroundAbsoluteGrid());
}

std::shared_ptr<BackgroundAbsoluteGrid> BackgroundAbsoluteGrid::Create(std::string backgroundPath)
{
	auto instance = std::shared_ptr<BackgroundAbsoluteGrid>(new BackgroundAbsoluteGrid());
	instance->SetBackground(backgroundPath);

	return instance;
}
