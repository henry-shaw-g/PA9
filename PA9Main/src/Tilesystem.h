#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

#include "SFML/Graphics.hpp"

#include "math/Vec2.h"
#include "resources/ResourceManager.h"
#include "kinematics/Body.h"

class Tile {

class Tile: public sf::RectangleShape
{
public:

	Tile();

	Tile(const sf::Vector2f& newSize, const sf::Vector2f& position, const sf::Color& newColor);

	bool getVisible() const;

	bool getIsWall() const;

	void setIsWall(bool isWall);

	void setColor(const sf::Color& color);

	void debug_setVisited(bool visited);

private:
	sf::Color color;
	bool isWall = false;
	bool debug_visited = false; // flag if the the wall was visited in the last collision update
};

	bool wall = false; //If the space has a wall on it
	Vector2f upperBound; //coordinates of the upper left corner
	Vector2f lowerBound; //coordinates of the lower right corner

public:

	Tile(Vector2f upper, Vector2f lower) {
		upperBound = upper;
		lowerBound = lower;
	}

	Tile() {
		wall = false;
	}

	void assignBounds(int column, int row);

	void setWall() {
		wall = true;
	} 

};

//class Tile: public sf::RectangleShape
//{
//public:
//
//	//desc: default constructor
//	Tile() {}
//
//	//desc: constructor
//	Tile(const sf::Vector2f& newSize, const sf::Vector2f& position, const sf::Color& newColor) : sf::RectangleShape(newSize) { //make a rectangle shape
//		this->setPosition(position); //set the position of the rectangle
//		this->setFillColor(newColor); //changes the color of the wall
//	}
//
//	//desc: set whether tiles are a wall ???
//	void setIsWall(bool isWall) { wall = isWall; }
//
//	//desc: returns a bool to whether a wall is on the tile
//	bool getIsWall() const { return wall; }
//
//private:
//
//	bool wall = false; //member stating whether a wall is on the tile
//};
//
//
///*
//Board Class: might move later
//*/
//
//class Tiles : public sf::Drawable {
//	using uint = unsigned int;
//public:
//	// ctor:
//	Tiles();
//
//	// dtor:
//	~Tiles();
//
//	// desc: check if the tiles at the grid coordinate are collidable (wall there)
//	// precond: col and row are within grid
//	bool canTileCollide(uint col, uint row) const;
//
//	// desc: get the dimensions of a single tile
//	Vector2f getTileSize() const;
//
//	// desc: get the dimensions of the tile grid
//	Vector2u getGridSize() const;
//
//	// desc: render the tiles (adheres to SFML draw idiom)
//	void draw(sf::RenderTarget& renderTarget, sf::RenderStates _) const override;
//
//private:
//	Tile* tileArray; // todo: consider using array or vector class here
//	const Vector2f tileSize;
//	const Vector2u gridSize;
//
//	// desc: utility to get tile index
//	uint indexFromColRow(uint col, uint row) const;
//};
