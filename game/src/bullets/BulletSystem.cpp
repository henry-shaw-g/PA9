/*
	file: BulletSystem.cpp
	desc: implements the bullet system
*/
#include "BulletSystem.h"

BulletSystem::BulletSystem(BodySystem& bodySystem) :
	bodySystemRef(bodySystem) {}

void BulletSystem::update(float dt) {
	BulletEvent event;
	Vector2f p0, p1;
	LineCastResult castResult;
	bool expired = false;
	for (int i = bullets.size() - 1; i >= 0; --i) {
		Bullet& bullet = bullets[i];
		// check expiration
		expired = bullet.update(dt, p0, p1);
		if (expired) {
			removeBullet(i);
			continue;
		}
		// check collisions
		castResult = bodySystemRef.lineCast(p0, p1);
		if (castResult.type == LineCastResult::Tile) {
			bounceBullet(bullet, castResult.data.point, castResult.data.normal);
		}
		else if (castResult.type == LineCastResult::Body) {
			removeBullet(i);
			event.type = BulletEvent::HitBody;
			event.hitBody.bodyId = castResult.bodyResult.id;
			event.hitBody.pos = castResult.data.point;
			event.hitBody.norm = castResult.data.normal;
			events.push(event);
		}
	}
}

void BulletSystem::draw(sf::RenderTarget& renderTarget, sf::RenderStates _) const {
	for (auto& bullet : bullets) {
		renderTarget.draw(bullet);
	}
}

bool BulletSystem::pollEvent(BulletEvent& event) {
	if (events.empty()) {
		return false;
	}
	else {
		event = events.front();
		events.pop();
		return true;
	}
}

void BulletSystem::addBullet(Vector2f pos, Vector2f vel, float lifetime) {
	bullets.push_back(Bullet(pos, vel, lifetime));
}

void BulletSystem::removeBullet(int index) {
	bullets[index] = bullets[bullets.size() - 1];
	bullets.pop_back();
}

void BulletSystem::bounceBullet(Bullet& bullet, Vector2f pos, Vector2f norm) {
	Vector2f v0 = bullet.getVelocity();
	Vector2f v0_tang = Vec2::dot(v0, norm) * norm; // math 220 and 172 coming in clutch here
	Vector2f v0_perp = v0 - v0_tang;
	bullet.setPosition(pos);
	bullet.setVelocity(v0_perp - v0_tang);
}