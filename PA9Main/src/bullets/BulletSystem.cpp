/*
	file: BulletSystem.cpp
*/
#include "BulletSystem.h"

void BulletSystem::update(float dt) {
	Vector2f p0, p1;
	bool expired = false;
	for (int i = bullets.size() - 1; i >= 0; --i) {
		Bullet& bullet = bullets[i];
		expired = bullet.update(dt, p0, p1);
		if (expired)
			removeBullet(i);
	}
}

void BulletSystem::draw(sf::RenderTarget& renderTarget, sf::RenderStates _) const {
	for (auto& bullet : bullets) {
		renderTarget.draw(bullet);
	}
}

void BulletSystem::addBullet(Vector2f pos, Vector2f vel, float lifetime) {
	bullets.push_back(Bullet(pos, vel, lifetime));
}

void BulletSystem::removeBullet(int index) {
	bullets[index] = bullets[bullets.size() - 1];
	bullets.pop_back();
}