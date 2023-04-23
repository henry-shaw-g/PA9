/*
	file: Vec2.h
	desc:
		- SFML Vec2 is lacking
		- inheriting the Vec2 class was getting messy, so just changed to using procedureal functions
*/
#pragma once

#include <iostream>

#include "SFML/System.hpp"

namespace Vec2 {
	using sf::Vector2f; // my poor fingies

	// operator: stream insertion
	// desc: for debugging by printing vector
	std::ostream& operator << (std::ostream& lhs, const Vector2f& rhs);

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


/* OLD Vec2f DERIVED CLASS (DO NOT USE) */

class Vec2f : public sf::Vector2f {
public:

	const static Vec2f Zero;

	// ctor: default
	// desc: initailizes to zero vector
	Vec2f();

	// ctor: from components
	Vec2f(float x, float y);
	
	// ctor: copy
	Vec2f(const sf::Vector2f& copy);
	
	// operator: = 
	// desc: necessary bcus = doesn't get inherited?
	Vec2f& operator= (const sf::Vector2f& lhs);

	// operator <<
	// desc: print the vector
	friend std::ostream& operator<< (std::ostream& lhs, const Vec2f& rhs);

	// desc: get magnitude
	float mag() const;

	// desc: get normalized (unit magnitude)
	Vec2f norm() const;

	// desc: compute dot product
	float dot(const Vec2f& lhs) const;

	// desc: compute in-plane R3 cross products (vectors normal to the vectors)
	Vec2f rcross() const;
	Vec2f lcross() const;
private:

};