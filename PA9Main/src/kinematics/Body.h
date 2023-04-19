#pragma once

class Body{

private:

	sf::Vector2f position;
	double velocity;

public:

	//Body object constructor
	Body(float xPos, float yPos) {
		position = sf::Vector2f(xPos, yPos);
		velocity = 0;
	}

	//Change the value of the velocity
	void setVelocity(double newVelocity) {
		velocity = newVelocity;
	}

	//Get the current Velocity of the object
	double getVelocity() { //might make virtual to make sure walls always return a value of 0
		return velocity;
	}

	//Change the position of the object
	void setCurrentPosition(float newX, float newY) {
		position.x = newX;
		position.y = newY;
	}

	//Get the current position of the object
	sf::Vector2f getCurrentPosition() {
		return position;
	}

	virtual void moveObject(sf::RenderWindow& window) = 0;
};