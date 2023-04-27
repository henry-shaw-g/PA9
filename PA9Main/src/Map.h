#pragma once

#include "Tile.h"

class Map {

private:

	Tile playSpace[32][18];

	// desc: set map to empty
	void emptyMap() {
		int row, col;

		for (col = 0; col < 32; ++col) {
			for (row = 0; row < 18; ++row) {
				playSpace[col][row].setEmpty();
			}
		}
	}
public:

	// desc: map 1
	static void loadMap1(Map& map);

	//desc: default constructor
	Map();

	//desc: goes through the tiles to check if there is a wall on it
	void printMap(sf::RenderTarget& renderTarget);

	Vector2u mapSize() {
		return Vector2u(32, 18);
	}

	Vector2f tileSize() {
		return Vector2f(15.0f, 15.0f);
	}

	Tile& getTile(int col, int row) {
		return	playSpace[col][row];
	}
};