#pragma once
#include <memory>
#include <set>

#include "Control.h"

class AbsoluteGrid : public Control
{
	public:
		virtual ~AbsoluteGrid();

		void AddChild(std::shared_ptr<Control> control);
		void RemoveChild(std::shared_ptr<Control> control);

		bool SetParent(std::shared_ptr<Control> parent) override;
		bool RemoveParent(std::shared_ptr<Control> parent) override;
		void SetPosition(float x, float y) override;

		sf::Vector2f GetSize() override;

		virtual bool TakeFocus(Focusable *requester) override;

		static std::shared_ptr<AbsoluteGrid> Create();

	protected:
		AbsoluteGrid();

		virtual void RunDraw(sf::RenderTexture *canvas) override;

		virtual void SetFocus() override;
		virtual void RemoveFocus() override;

		void RunTick(std::shared_ptr<TickState_t> state) override;

		std::shared_ptr<std::set<std::shared_ptr<Control>>> CopyChilds();

	private:
		std::shared_ptr<std::set<std::shared_ptr<Control>>> m_Childs = nullptr;
		std::shared_ptr<std::set<std::shared_ptr<Control>>> m_NextTickChilds = nullptr;

		std::unique_ptr<sf::Mutex> m_ChildMutex = nullptr;
};

