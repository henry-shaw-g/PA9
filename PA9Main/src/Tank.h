#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

#include "SFML/Graphics.hpp"

#include "math/Vec2.h"
#include "resources/ResourceManager.h"
#include "kinematics/CircleBody.h"

class Tank : public CircleBody, public sf::Drawable {

public:

	// enum for colors of tanks
	enum class Type {
		Red,
		Blue,
	};

	Vector2f getFrontDir() const;
	Vector2f getRightDir() const;

	// ctor: initialize tank with position and collider radius
	Tank(float initX, float initY, float radius, Tank::Type type);

	// desc: render the tank
	void draw(sf::RenderTarget& renderTarget, sf::RenderStates _) const override;

	void setRadians() {
		radians = (M_PI / 180) * getRotation();
	}

	float getMaxAngV() {
		return maxAngV;
	}

	// desc: set the various input states
	void setForward(float input);
	void setBack(float input);
	void setLeft(float input);
	void setRight(float inptu);

	// desc: update the tank (handle controls)
	void update(float dt);

	// desc: fire projectile from tank
	void shoot(float& xVal, float& yVal);

private:

	Tank::Type tankType;

	float maxV;
	float maxAngV;
	float radians;

	float forwardInput;
	float backInput;
	float leftInput;
	float rightInput;

	sf::Sprite chassisSprite;
	//sf::Sprite turretSprite;
};