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
	Tile(const sf::Vector2f& newSize, const sf::Vector2f& position, const sf::Color& newColor) : sf::RectangleShape(newSize) {
	this->setPosition(position);
	this->setFillColor(newColor);
	}

private:

};




void uppercoordinate(int height, sf::Vector2f array[],  int index, int i)
{
	if (height == 18)
	{
		return;
	}
	if (index == 15)
	{
		++height;
		index = 0;
	}
	array[i] = sf::Vector2f(index * 32, height * 18);
	++index;
	++i;
	uppercoordinate(height, array, index, i);

}

void lowercoordinate(int height, sf::Vector2f array[], int index, int i)
{
	if (height == 18)
	{
		return;
	}
	if (index == 15)
	{
		++height;
		index = 0;
	}
	array[i] = sf::Vector2f(index * 32, height * 18);
	++index;
	++i;
	lowercoordinate(height, array, index, i);
}