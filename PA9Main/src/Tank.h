#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

#include "SFML/Graphics.hpp"

#include "math/Vec2.h"
#include "resources/ResourceManager.h"
#include "kinematics/CircleBody.h"

class Tank : public CircleBody, public sf::Drawable {

private:

	float maxV;
	float maxAngV;
	float radians;

	sf::Sprite chassisSprite;
	sf::Sprite turretSprite;

	Vector2f getFrontDir() const;
	Vector2f getRightDir() const;

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