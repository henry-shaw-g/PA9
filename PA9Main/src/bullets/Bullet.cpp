/*
	file: Bullet.cpp
	desc: implements Bullet class
*/

#include <cmath>

#include "../resources/ResourceManager.h"
#include "../math/Misc.h"
#include "Bullet.h"

Bullet::Bullet(Vector2f pos, Vector2f vel) {
	setPosition(pos);
	setVelocity(vel);
	setTexture(ResourceManager::service().getTextureRef("bullet"));
}

void Bullet::update(float dt, Vector2f& p0, Vector2f& p1) {
	p0 = getPosition();
	p1 = p0 + velocity * dt;
	setPosition(p1);
}

void Bullet::setVelocity(Vector2f vel) {
	velocity = vel;
	float rad = math::toDeg(std::atan2f(vel.x, -vel.y));
	setRotation(rad);
}