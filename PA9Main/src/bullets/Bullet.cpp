/*
	file: Bullet.cpp
	desc: implements Bullet class
*/

#include <cmath>

#include "../resources/ResourceManager.h"
#include "../math/Misc.h"
#include "Bullet.h"

Bullet::Bullet(Vector2f pos, Vector2f vel, float maxLifetime) {
	setPosition(pos);
	setVelocity(vel);
	setTexture(ResourceManager::service().getTextureRef("bullet"));
	lifetime = maxLifetime;
}

bool Bullet::update(float dt, Vector2f& p0, Vector2f& p1) {
	p0 = getPosition();
	p1 = p0 + velocity * dt;
	setPosition(p1);

	lifetime -= dt;
	return lifetime < 0;
}

void Bullet::setVelocity(Vector2f vel) {
	velocity = vel;
	float rad = std::atan2f(vel.y, vel.x);
	float deg = math::toDeg(rad);
	setRotation(deg);
}