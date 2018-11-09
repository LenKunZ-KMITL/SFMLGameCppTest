#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <string>

#include "AbsoluteGrid.h"
#include "SpriteUtils.h"

class BackgroundAbsoluteGrid :
	public AbsoluteGrid
{
	public:
		~BackgroundAbsoluteGrid();

		void SetBackground(std::string backgroundPath);
		void RemoveBackground(std::string backgroundPath);

		virtual bool SetParent(std::shared_ptr<Control> parent);
		virtual bool RemoveParent(std::shared_ptr<Control> parent);

		static std::shared_ptr<BackgroundAbsoluteGrid> Create();
		static std::shared_ptr<BackgroundAbsoluteGrid> Create(std::string backgroundPath);

	protected:
		BackgroundAbsoluteGrid();

		virtual void RunDraw(sf::RenderTexture *canvas) override;

	private:
		std::shared_ptr<SpriteControlModifier> m_BackgroundSprite = nullptr;
};

