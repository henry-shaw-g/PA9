#include "Map.h"

Map::Map() {

	for (int column = 0; column < 32; ++column) {
		for (int row = 0; row < 18; ++row) {

			playSpace[column][row].assignBounds(column, row);

		}
	}

	emptyMap();
}

//desc: goes through the tiles to check if there is a wall on it
void Map::printMap(sf::RenderTarget& renderTarget) {
	
	for (int column = 0; column < 32; ++column) {
		for (int row = 0; row < 18; ++row) {

			if (playSpace[column][row].isWall() == true) {

				sf::RectangleShape newWall(Vector2f(15, 15));
				newWall.setFillColor(sf::Color::Black);
				newWall.setPosition(playSpace[column][row].getUpperBound());
				renderTarget.draw(newWall);
			}

		}
	}
}

//desc: assigns a wall to the current tile
void Map::loadMap1(Map& map) {
	map.emptyMap();

	for (int horizon = 0; horizon < 8; ++horizon) {
		map.getTile(2 + horizon,3).setWall();
		map.getTile(2 + horizon,14).setWall();
		map.getTile(22 + horizon,3).setWall();
		map.getTile(22 + horizon,14).setWall();
	}

	for (int vert = 0; vert < 6; ++vert) {
		map.getTile(10, 6 + vert).setWall();
		map.getTile(21, 6 + vert).setWall();
	}

	for (int vert = 0; vert < 4; ++vert) {
		map.getTile(15, 3 + vert).setWall();
		map.getTile(16, 3 + vert).setWall();
		map.getTile(15, 11 + vert).setWall();
		map.getTile(16, 11 + vert).setWall();
	}
}