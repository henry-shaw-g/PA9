/*
	file: Vec2.h
	desc: SFML Vec2 is lacking
*/
#pragma once

#include "SFML/System.hpp"

class Vec2f : public sf::Vector2f {
public:

	// ctor: default
	// desc: initailizes to zero vector
	Vec2f();

	// ctor: from components
	Vec2f(float x, float y);
	
	// ctor: copy
	Vec2f(const Vec2f& copy);
	Vec2f(const sf::Vector2f& copy);
	
	// operator: = 
	// desc: necessary bcus = doesn't get inherited?
	Vec2f& operator= (const Vec2f& lhs);
	Vec2f& operator= (const sf::Vector2f& lhs);

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

