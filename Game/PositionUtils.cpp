#include "PositionUtils.h"

bool PositionUtils::IsPositionInBound(sf::Vector2f position, sf::Vector2f boundPosition, sf::Vector2f boundSize)
{
	return position.x >= boundPosition.x &&
		position.y >= boundPosition.y &&
		position.x <= boundPosition.x + boundSize.x &&
		position.y <= boundPosition.y + boundSize.y;
}

sf::Vector2f PositionUtils::GetAbsolutePosition(sf::Vector2f boundPosition, sf::Vector2f position) 
{
	return sf::Vector2f(boundPosition.x + position.x, boundPosition.y + position.y);
}

sf::Vector2f PositionUtils::GetRelativePosition(sf::Vector2f boundPosition, sf::Vector2f absolutePosition) {
	return sf::Vector2f(absolutePosition.x - boundPosition.x, absolutePosition.y - boundPosition.y);
}