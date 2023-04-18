#pragma once

#define _USE_MATH_DEFINES
#include <math.h>
#include "SFML/Graphics.hpp"
#include "ResourceManager.h"
#include "Body.h"

class Tank : public Body, public sf::CircleShape{

private:

	float maxV;
	float maxAngV;
	float radians;

public:

	Tank(float initX, float initY, float radius) : Body(initX, initY), CircleShape(radius) {
		maxV = .1;
		maxAngV = 5;
		radians = 0;
		this->setPosition(getCurrentPosition());
		this->setOrigin(radius, radius);
		
	}

	void setRadians() {
		radians = (M_PI / 180) * getRotation();
	}

	void moveObject(sf::RenderWindow& window);
};