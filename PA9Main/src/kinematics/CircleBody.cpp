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
	circle.setPosition(position);
	renderTarget.draw(circle);
}