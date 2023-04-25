/*
	file: TileSystem.cpp
	desc: implement TileSystem.h
*/

#include "TileSystem.h"

void Tile::assignBounds(int column, int row) {

	upperBound = Vector2f(column * 15, row * 15);
	lowerBound = Vector2f((column + 1) * 15, (row + 1) * 15);

}

void Tile::draw(sf::RenderTarget& renderTarget, sf::RenderStates _) const {

	sf::RectangleShape newWall(Vector2f(15,15));
	newWall.setPosition(Vector2f(getUpperBound()));
	newWall.setFillColor(sf::Color::Black);
	
	renderTarget.draw(newWall);
}
