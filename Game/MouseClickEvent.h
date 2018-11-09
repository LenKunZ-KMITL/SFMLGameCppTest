#pragma once
#include <SFML/Graphics.hpp>
#include "EventListener.h"

typedef struct MouseClickEventArgs {
	sf::Vector2f Position;
	sf::Vector2f AbsolutePosition;
	sf::Mouse::Button Button;
} MouseClickEventArgs_t;

class MouseClickEvent : public EventListener<MouseClickEventArgs_t> {
	public:
		MouseClickEvent();
		virtual ~MouseClickEvent();
};