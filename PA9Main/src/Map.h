#pragma once

#include "Tilesystem.h"

class Map {

private:

	Tile playSpace[32][18];

	//desc: assigns a wall to the current tile
	void assignWalls();

public:

	//desc: default constructor
	Map();

	//desc: goes through the tiles to check if there is a wall on it
	void printMap(sf::RenderWindow& window);

	Vector2f mapSize() {
		return Vector2f(32.0f, 18.0f);
	}

	Vector2f tileSize() {
		return Vector2f(15.0f, 15.0f);
	}
};