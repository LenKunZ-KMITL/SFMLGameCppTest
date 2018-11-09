#pragma once
#include <cstdint>
#include <functional>
#include <memory>
#include <set>
#include <SFML/Graphics.hpp>

#include "Control.h"

class ManagedWindow : public Control
{
    public:
        static const int DEFAULT_FRAMERATE = 60;
        static const int DEFAULT_TICKRATE = 60;

		~ManagedWindow();

        void AddChild(std::shared_ptr<Control> control);
        void RemoveChild(std::shared_ptr<Control> control);

        void SetFramerate(long framerate);
        long GetFramerate();

        void SetTickrate(long tickrate);
        long GetTickrate();

		bool FrameThreadEnabled = true;
		bool TickThreadEnabled = true;

		bool IsValid();
		void Terminate();

		virtual sf::Vector2f GetSize();

		void Wait();

		static std::shared_ptr<ManagedWindow> Create(std::function<std::shared_ptr<sf::RenderWindow>()> creator);

	protected:
		ManagedWindow(std::function<std::shared_ptr<sf::RenderWindow>()> parent);
		virtual void RunTick(std::shared_ptr<TickState_t> tickState) override;
		virtual void RunDraw(sf::RenderTexture *canvas) override;

	private:
		void Start();

		void InitThreads();
		void FrameThread();
		void TickThread();

		std::unique_ptr<sf::Mutex> m_StartMutex;

		std::unique_ptr<sf::Mutex> m_FrameMutex;
		std::unique_ptr<sf::Mutex> m_TickMutex;

        std::unique_ptr<sf::Thread> m_FrameThread = nullptr;
		std::unique_ptr<sf::Thread> m_TickThread = nullptr;

		std::unique_ptr<std::function<void(sf::RenderWindow)>> m_RenderFunction;

        std::shared_ptr<sf::RenderWindow> m_Parent;
        std::unique_ptr<std::set<std::shared_ptr<Control>>> m_Controls;

		bool m_Terminated = false;

        int m_Framerate;
        int m_Tickrate;

        int64_t m_FramePeriodMicroseconds = 0;
        int64_t m_TickPeriodMicroseconds = 0;

        std::unique_ptr<sf::Clock> m_FrameClock;
        std::unique_ptr<sf::Clock> m_TickClock;

		bool m_Started = false;

		std::function<std::shared_ptr<sf::RenderWindow>()> m_Creator;
};
