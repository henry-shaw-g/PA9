/*
	file: TileSystem.cpp
	desc: implement TileSystem.h
*/

#include "TileSystem.h"

/* TILE */

Tile::Tile() {
	setColor(sf::Color::Black);
	this->setOutlineColor(sf::Color::Red);
	this->setOutlineThickness(0.f);
}

bool Tile::getVisible() const {
	return isWall || debug_visited;
}

void Tile::setIsWall(bool setWall) { 
	isWall = setWall; 
	if (isWall)
		setFillColor(color);
	else
		setFillColor(sf::Color::Transparent);
		
}

bool Tile::getIsWall() const { 
	return isWall; 
}

void Tile::setColor(const sf::Color& newColor)
{
	color = newColor;
	if (isWall) {
		setFillColor(color);
	}
}

void Tile::debug_setVisited(bool visited) {
	debug_visited = visited;
	this->setOutlineThickness(debug_visited ? 2.f : 0.f);
}

/* TILES */

Tiles::Tiles() :
	tileSize(30.f, 30.f), gridSize(16, 9) // < TEMP
{
	tileArray = new Tile[gridSize.x * gridSize.y];
	int row, col;
	for (row = 0; row < gridSize.y; ++row) {
		for (col = 0; col < gridSize.x; ++col) {
			Tile& t = tileArray[indexFromColRow(col, row)];
			t.setPosition(Vector2f(col * tileSize.x, row * tileSize.y));
			t.setSize(tileSize);
			t.setColor(sf::Color(64, 64, 64));
			t.setIsWall(false);
		}
	}

}

Tiles::~Tiles()
{
	delete[] tileArray;
}

Tile& Tiles::getTile(int col, int row) const {
	return tileArray[indexFromColRow(col, row)];
}

bool Tiles::canTileCollide(int col, int row) const
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
	for(int i = 0; i < gridSize.x * gridSize.y; ++i) {
		Tile& tile = tileArray[i];
		if (tile.getVisible()) {
			renderTarget.draw(tile);
		}
		tile.debug_setVisited(false);
	}
}

int Tiles::indexFromColRow(int col, int row) const
{
	return gridSize.x * row + col;
}

