/*
	file: Body.h
	desc: high level body class
*/
#pragma once

#include "../math/Vec2.h"

typedef unsigned int uint;

class Body{

private:
	unsigned int index; // index of the body in the list it resides in? (needs to be accessible from both the users and the body sytem)

public:

	// moved these to public for ease of use
	Vec2f position;
	Vec2f velocity;

	//Body object constructor
	Body(float xPos, float yPos) {
		position = Vec2f(xPos, yPos);
		velocity = Vec2f(0.f, 0.f);
		index = -1;
	}

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
};