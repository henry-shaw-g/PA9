/*
	file: CircleBody.cpp
	desc: implements CircleBody class
*/

#include "CircleBody.h"

void CircleBody::debug_draw(sf::RenderTarget& renderTarget) const {
	sf::CircleShape circle(radius, 16);
	circle.setFillColor(sf::Color::Transparent);
	circle.setOutlineColor(sf::Color::Red);
	circle.setOutlineThickness(2.f);
	circle.setRadius(radius);
	circle.setOrigin(radius, radius);
	renderTarget.draw(circle, getTransform());
}

sf::FloatRect CircleBody::getAABB() const
{
	Vector2f position = getPosition();
	Vector2f r(radius, radius);
	return sf::FloatRect(position - r, 2.f * r);
}
