#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

#include "SFML/Graphics.hpp"

#include "math/Vec2.h"
#include "resources/ResourceManager.h"
#include "kinematics/Body.h"

class Tile: public sf::RectangleShape {

private:

	// desc: utility to get tile index

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

	Vector2f getUpperBound() const{
		return upperBound;
	}

	void assignBounds(int column, int row);

	void setEmpty() {
		wall = false;
	}

	void setWall() {
		wall = true;
	} 

	bool isWall() {
		return wall;
	}

	// desc: render the tiles (adheres to SFML draw idiom)
	void draw(sf::RenderTarget& renderTarget, sf::RenderStates _) const override;
};

