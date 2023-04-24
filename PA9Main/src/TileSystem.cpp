/*
	file: TileSystem.cpp
	desc: implement TileSystem.h
*/

#include "TileSystem.h"

using uint = unsigned int;

// ctor: default
Tiles::Tiles() :
	tileSize(30.f, 30.f), gridSize(16, 9)
{
	tileArray = new Tile[gridSize.x * gridSize.y];
	uint row, col;
	for (row = 0; row < gridSize.y; ++row) {
		for (col = 0; col < gridSize.x; ++col) {
			Tile& t = tileArray[indexFromColRow(col, row)];
			t.setPosition(sf::Vector2f(col * tileSize.x, row * tileSize.y));
			t.setSize(tileSize);
			t.setFillColor(sf::Color(64, 64, 64));
			t.setIsWall(false);
		}
	}

	// temp map:
	tileArray[indexFromColRow(1, 1)].setIsWall(true);
	tileArray[indexFromColRow(2, 1)].setIsWall(true);
	tileArray[indexFromColRow(3, 1)].setIsWall(true);
	tileArray[indexFromColRow(4, 1)].setIsWall(true);
}

Tiles::~Tiles()
{
	delete[] tileArray;
}

bool Tiles::canTileCollide(uint col, uint row) const
{
	Tile& tile = tileArray[indexFromColRow(col, row)];
	return tile.getIsWall();
}

Vector2f Tiles::getTileSize() const
{
	return tileSize;
}

Vector2u Tiles::getGridSize() const
{
	return gridSize;
}

void Tiles::draw(sf::RenderTarget& renderTarget, sf::RenderStates _) const
{
	for(uint i = 0; i < gridSize.x * gridSize.y; ++i) {
		Tile& tile = tileArray[i];
		if (tile.getIsWall())
			renderTarget.draw(tile);
	}
}

uint Tiles::indexFromColRow(uint col, uint row) const
{
	return gridSize.y * row + col;
}

