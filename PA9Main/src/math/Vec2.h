/*
	file: Vec2.h
	desc:
		- SFML Vec2 is lacking
		- inheriting the Vec2 class was getting messy, so just changed to using procedureal functions
*/
#pragma once

#include <iostream>

#include "SFML/System.hpp"
using sf::Vector2f; // my poor fingies (note: this in header scope so will be usable in all including files)
using sf::Vector2u;
using sf::Vector2i;

namespace Vec2 {
	// func: mag()
	// desc: get magnitude of the vector
	float mag(Vector2f v);

	// func: norm()
	// desc: get the normal of the vector
	// note: returns zero vector if input is zero vector
	Vector2f norm(Vector2f v);

	// func: dot()
	// desc: dot product operation
	float dot(Vector2f u, Vector2f v);

	// func: cross()
	// desc: compute in-plane R3 cross products (vectors normal to the vectors)
	Vector2f rcross(Vector2f v);
	Vector2f lcross(Vector2f v);

	// utility constants
	const extern Vector2f Zero;
	const extern Vector2f I;
	const extern Vector2f J;
}

// operator: stream insertion
// desc: for debugging by printing vector
std::ostream& operator << (std::ostream& lhs, const Vector2f& rhs);