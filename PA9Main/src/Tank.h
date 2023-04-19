#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

#include "SFML/Graphics.hpp"

#include "math/Vec2.h"
#include "resources/ResourceManager.h"
#include "kinematics/Body.h"

class Tank : public Body, public sf::CircleShape {

private:

	float maxV;
	float maxAngV;
	float radians;

	sf::Sprite chassisSprite;
	sf::Sprite turretSprite;

	Vec2f getFrontDir() const;
	Vec2f getRightDir() const;

public:

	// ctor: initialize tank with position and collider radius
	Tank(float initX, float initY, float radius);

	// desc: render the tank
	void draw(sf::RenderTarget& renderTarget, sf::RenderStates _) const override;

	void setRadians() {
		radians = (M_PI / 180) * getRotation();
	}

	void moveObject();
};