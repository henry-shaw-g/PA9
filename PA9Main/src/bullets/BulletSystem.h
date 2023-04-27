/*
	file: BulletSystem.h
*/
#pragma once

#include <vector>
#include <queue>

#include "SFML/Graphics.hpp"

#include "../math/Vec2.h"
#include "../kinematics/BodySystem.h"
#include "Bullet.h"

// bullet event record for clients (SFML style)
struct BulletEvent {
public:
	BulletEvent() {}

	enum Type {
		HitBody,
		None,
	};

	struct HitBodyEvent {
		int bodyId = 0;
		Vector2f pos = Vec2::Zero;
		Vector2f norm = Vec2::Zero;
	};

	Type type = None;
	union {
		HitBodyEvent hitBody;
	};
};

class BulletSystem : public sf::Drawable {
public:
	// desc: initialize, and dependency inject the body system
	BulletSystem(BodySystem& bodySystem);

	// desc: update
	void update(float dt);

	// desc: render
	void draw(sf::RenderTarget& renderTarget, sf::RenderStates _) const override;

	// desc: get bullet events
	// returns: true if there was an event to poll
	bool pollEvent(BulletEvent& event);

	// desc: add bullet
	void addBullet(Vector2f pos, Vector2f vel, float lifetime);
private:
	// desc: utility to remove a bullet at index (performs swap operation)
	// precond: not empty
	// note: this will cause elements to be skipped if forward iterating
	void removeBullet(int index);

	// desc: execute a bounce for a bullet (not putting in bullet class to adhere to sep. of concerns)
	void bounceBullet(Bullet& bullet, Vector2f pos, Vector2f norm);

	BodySystem& bodySystemRef;
	std::vector<Bullet> bullets;
	std::queue<BulletEvent> events;
};