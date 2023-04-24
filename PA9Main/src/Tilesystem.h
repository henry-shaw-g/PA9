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
	Tile() {}
	Tile(const sf::Vector2f& newSize, const sf::Vector2f& position, const sf::Color& newColor) : sf::RectangleShape(newSize) {
		this->setPosition(position);
		this->setFillColor(newColor);
	}

	void setIsWall(bool isWall) { wall = isWall; }
	bool getIsWall() const { return wall; }
private:
	bool wall = false;
};

class Tiles : public sf::Drawable {
	using uint = unsigned int;
public:
	// ctor:
	Tiles();

	// dtor:
	~Tiles();

	// desc: check if the tiles at the grid coordinate are collidable (wall there)
	// precond: col and row are within grid
	bool canTileCollide(uint col, uint row) const;

	// desc: get the dimensions of a single tile
	Vector2f getTileSize() const;

	// desc: get the dimensions of the tile grid
	Vector2u getGridSize() const;

	// desc: render the tiles (adheres to SFML draw idiom)
	void draw(sf::RenderTarget& renderTarget, sf::RenderStates _) const override;

private:
	Tile* tileArray; // todo: consider using array or vector class here
	const Vector2f tileSize;
	const Vector2u gridSize;

	// desc: utility to get tile index
	uint indexFromColRow(uint col, uint row) const;
};

// commented out because was getting linker errors from it
/*
// what this:
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
*/