/*
	file: Bullet.h
	desc: Bullet class, essentially just a container for bullet information and potentially state? 
*/
#pragma once

#include "SFML/Graphics.hpp"

#include "../math/Vec2.h"

class Bullet : public sf::Sprite {
public:
	
	// ctor:
	// desc: create with position and velocity
	Bullet(Vector2f pos, Vector2f vel, float maxLifetime);

	// desc: update the bullet velocity, potentially handle collision?
	// args: dt: time step length, p0 (OUT): position pre-update, p1 (OUT): position post-update
	// returns: bool, if bullet is expiring
	bool update(float dt, Vector2f& p0, Vector2f& p1);

	// desc: set the bullet velocity (also updats the sprite transform)
	void setVelocity(Vector2f vel);
private:

	Vector2f velocity;
	float lifetime;
};