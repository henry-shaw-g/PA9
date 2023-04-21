/*
	file: AxisBoxBody.h
	desc: 
		- class for axis aligned box bodies (no rotation)
		- the position inherited from body represents the mid point of the box	
*/

#pragma once

#include "SFML/Graphics.hpp"

#include "../math/Vec2.h"
#include "Body.h"

typedef unsigned int uint;

// note: not inheriting from body since all this contains is positional data
class AxisBoxBody : private sf::FloatRect {
public:
	// desc: factory that constructs a box body from a tile
	static AxisBoxBody fromTile(uint col, uint row, float tileW, float tileH);

	// desc: get width of box rect
	float getWidth() const;

	// desc: get height of box rect
	float getHeight() const;

	// desc: get the y position of the top of the rect
	float getTop() const;

	// desc: get the y position of the bottom of the rect
	float getBottom() const;

	// desc: get the y position of the left of the rect
	float getLeft() const;

	// desc: get the x position of the right of the rect
	float getRight() const;

	// desc: get center point
	Vec2f getPosition() const;

	// desc: for debugging purposes
	void debug_draw(sf::RenderTarget& renderTarget) const;
};