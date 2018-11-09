#pragma once

#include <SFML/Graphics.hpp>
#include <set>
#include <memory>

typedef struct TickState {
	std::set<sf::Event*> Events;
	sf::Vector2f MousePosition;
	bool MouseInBound = true;
	bool IsTab = true;
} TickState_t;