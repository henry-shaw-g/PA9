/*
	file: Body.h
	desc: high level body class
*/
#pragma once

#include "../math/Vec2.h"

class Body{

private:

	Vec2f position;
	Vec2f velocity;

public:

	//Body object constructor
	Body(float xPos, float yPos) {
		position = Vec2f(xPos, yPos);
		velocity = Vec2f(0.f, 0.f);
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

	//Get the current position of the object
	Vec2f getCurrentPosition() {
		return position;
	}

	virtual void moveObject() = 0;
};