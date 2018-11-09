#pragma once

#include <SFML/Graphics.hpp>

namespace PositionUtils {
	bool IsPositionInBound(sf::Vector2f mousePosition, sf::Vector2f boundPosition, sf::Vector2f boundSize);
	sf::Vector2f GetAbsolutePosition(sf::Vector2f boundPosition, sf::Vector2f position);
	sf::Vector2f GetRelativePosition(sf::Vector2f boundPosition, sf::Vector2f absolutePosition);
}