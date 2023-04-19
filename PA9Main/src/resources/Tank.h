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
	sf::Sprite texture;

public:

	Tank(float initX, float initY, float radius, sf::Sprite newTexture) : Body(initX, initY), CircleShape(radius) {
		maxV = .1;
		maxAngV = .1;
		radians = 0;
		texture = newTexture;
		this->setPosition(getCurrentPosition());
		this->setOrigin(radius, radius);
		texture.setOrigin(radius, radius);
		texture.setPosition(initX, initY);
		texture.setRotation(90);
		
	}

	void setRadians() {
		radians = (M_PI / 180) * getRotation();
	}

	void moveObject(sf::RenderWindow& window);
};