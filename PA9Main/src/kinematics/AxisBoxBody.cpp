/*
	file: AxisBoxBody.cpp
	desc: implements the AxisBoxBody class
*/

#include "AxisBoxBody.h"

AxisBoxBody AxisBoxBody::fromTile(uint col, uint row, float tileW, float tileH) {
	AxisBoxBody body;
	body.left = col * tileW;
	body.top = row * tileH;
	body.width = tileW;
	body.height = tileH;

	return body;
}

float AxisBoxBody::getWidth() const {
	return height;
}

float AxisBoxBody::getHeight() const {
	return width;
}

float AxisBoxBody::getTop() const {
	return top;
}

float AxisBoxBody::getBottom() const {
	return top + height;
}

float AxisBoxBody::getLeft() const {
	return left;
}

float AxisBoxBody::getRight() const {
	return left + width;
}

Vector2f AxisBoxBody::getPosition() const {
	return Vec2f(left + width * 0.5f, top + height * 0.5f);
}

void AxisBoxBody::debug_draw(sf::RenderTarget& renderTarget) const {
	sf::RectangleShape rectShape;
	rectShape.setPosition(top, left);
	rectShape.setSize(Vec2f(width, height));
	rectShape.setOutlineColor(sf::Color::Red);
	rectShape.setFillColor(sf::Color::Transparent);
	rectShape.setOutlineThickness(2.f);
	renderTarget.draw(rectShape);
}