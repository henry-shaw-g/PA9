/*
	file: Body.h
	desc: high level body class
*/
#pragma once

#include "SFML/Graphics.hpp"

#include "../math/Vec2.h" // Vector2f type and functions

typedef unsigned int uint;

enum class BodyType {
	Point	= 0,
	Circle	= 1 << 0,
	AABB	= 1 << 1,
};

class Body : public sf::Transformable {

private:
	unsigned int index; // index of the body in the list it resides in? (needs to be accessible from both the users and the body sytem)

public:

	// moved these to public for ease of use
	Vector2f velocity;

	//Body object constructor
	Body(Vector2f pos) :
		velocity(Vec2::Zero)
	{
		setPosition(pos);
		index = -1;
	}

	Body(float xPos, float yPos) :
		Body(Vector2f(xPos, yPos)) {}

	void resolveCollision(Vector2f offset) {
		setPosition(getPosition() - offset);
	}

	//Change the value of the velocity
	void setVelocity(Vector2f newVelocity) {
		velocity = newVelocity;
	}

	//Get the current Velocity of the object
	Vector2f getVelocity() { //might make virtual to make sure walls always return a value of 0
		return velocity;
	}

	// desc: get list index for body (internal to BodySystem)
	uint getIndex() {
		return index;
	}

	// desc: set list index for body (internal to BodySystem)
	void setIndex(uint nIndex) {
		index = nIndex;
	}

	virtual BodyType getType() const { return BodyType::Point; }

	virtual void debug_draw(sf::RenderTarget& rt) const {
		sf::CircleShape circle(3.f, 16);
		circle.setOrigin(circle.getRadius(), circle.getRadius());
		circle.setFillColor(sf::Color::Transparent);
		circle.setOutlineColor(sf::Color::Red);
		circle.setOutlineThickness(2.f);
		rt.draw(circle, getTransform());
	}
};