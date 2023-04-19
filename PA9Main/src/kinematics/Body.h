/*
	file: Body.h
	desc: high level body class
*/
#pragma once

#include "SFML/Graphics.hpp"

#include "../math/Vec2.h"

typedef unsigned int uint;

class Body {

private:
	unsigned int index; // index of the body in the list it resides in? (needs to be accessible from both the users and the body sytem)

public:

	// moved these to public for ease of use
	Vec2f position;
	Vec2f velocity;

	//Body object constructor
	Body(Vec2f pos) :
		position(pos), velocity(Vec2f::Zero)
	{
		index = -1;
	}

	Body(float xPos, float yPos) :
		Body(Vec2f(xPos, yPos)) {}

	//Change the value of the velocity
	void setVelocity(Vec2f newVelocity) {
		velocity = newVelocity;
	}

	//Get the current Velocity of the object
	Vec2f getVelocity() { //might make virtual to make sure walls always return a value of 0
		return velocity;
	}

	//Change the position of the object
	void setCurrentPosition(float newX, float newY) {
		position.x = newX;
		position.y = newY;
	}

	void setCurrentPosition(Vec2f newPosition) {
		position = newPosition;
	}

	//Get the current position of the object
	Vec2f getCurrentPosition() {
		return position;
	}

	// desc: get list index for body (internal to BodySystem)
	uint getIndex() {
		return index;
	}

	// desc: set list index for body (internal to BodySystem)
	void setIndex(uint nIndex) {
		index = nIndex;
	}

	virtual void debug_draw(sf::RenderTarget& rt) const {
		sf::CircleShape circle(5.f, 8);
		circle.setOrigin(circle.getRadius(), circle.getRadius());
		circle.setFillColor(sf::Color::Transparent);
		circle.setOutlineColor(sf::Color::Red);
		circle.setOutlineThickness(2.f);
		circle.setPosition(position);
		rt.draw(circle);
	}
};