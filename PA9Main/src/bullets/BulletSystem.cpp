/*
	
*/

#include "BulletSystem.h"

void BulletSystem::update(float dt) {
	Vector2f p0, p1;
	for (auto& bullet : bullets) {
		bullet.update(dt, p0, p1);
	}
}

void BulletSystem::draw(sf::RenderTarget& renderTarget, sf::RenderStates _) const {
	for (auto& bullet : bullets) {
		renderTarget.draw(bullet);
	}
}

void BulletSystem::addBullet(Vector2f pos, Vector2f vel) {
	bullets.push_back(Bullet(pos, vel));
}
