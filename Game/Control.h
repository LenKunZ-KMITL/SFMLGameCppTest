#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

#include "TickState.h"
#include "MouseClickEvent.h"
#include "ControlDrawEvent.h"
#include "Focusable.h"

class Control: public std::enable_shared_from_this<Control>, public Focusable
{
	public:
		virtual ~Control();

		std::shared_ptr<Control> GetSharedPtr();

		void Draw(sf::RenderTexture *canvas);
		void Tick(std::shared_ptr<TickState_t> state);

		virtual bool SetParent(std::shared_ptr<Control> parent);
		virtual bool RemoveParent(std::shared_ptr<Control> parent);
		virtual bool HasNextParent();
		virtual std::shared_ptr<Control> GetParent();

		virtual void SetPosition(float x, float y);
		virtual void SetSize(float width, float height);

		virtual sf::Vector2f GetPosition();
		virtual sf::Vector2f GetAbsolutePosition();
		virtual sf::Vector2f GetSize();

		std::unique_ptr<MouseClickEvent> MouseClick;
		std::unique_ptr<ControlDrawEvent> WhenDraw;

		virtual bool IsFocus() override;

		virtual void Focus() override;
		virtual void Blur() override;

		virtual bool TakeFocus(Focusable *requester) override;

		static std::shared_ptr<Control> Create();

	protected:
		Control();
		virtual void RunTick(std::shared_ptr<TickState_t> state);
		virtual void RunDraw(sf::RenderTexture *canvas);

		virtual void RunMouseClickEvent(std::shared_ptr<MouseClickEventArgs_t> args);

		virtual void SetFocus();
		virtual void RemoveFocus();

	private:
		std::shared_ptr<Control> m_ControlParent = nullptr;
		std::shared_ptr<Control> m_NextControlParent = nullptr;

		std::unique_ptr<sf::Mutex> m_DrawMutex;

		std::unique_ptr<sf::Mutex> m_ControlParentMutex;

		float m_X = 0, m_Y = 0;
		float m_Width = 0, m_Height = 0;

		bool m_Focusing = false;
};

