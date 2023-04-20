#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

#include "SFML/Graphics.hpp"

#include "math/Vec2.h"
#include "resources/ResourceManager.h"
#include "kinematics/Body.h"


class Tile: public sf::RectangleShape
{
public:
	Tile(sf::Vector2f& newSize, const sf::Vector2f& position, const sf::Color& newColor) : sf::RectangleShape(newSize) {
	this->setPosition(position);
	this->setFillColor(newColor);
	}


private:
	int width;
	int height;

};


