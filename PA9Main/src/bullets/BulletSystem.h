/*
	file: BulletSystem.h
*/
#pragma once

#include <vector>

#include "SFML/Graphics.hpp"

#include "../math/Vec2.h"
#include "Bullet.h"

class BulletSystem : public sf::Drawable {
public:

	// desc: update
	void update(float dt);

	// desc: render
	void draw(sf::RenderTarget& renderTarget, sf::RenderStates _) const override;

	// desc: add bullet
	void addBullet(Vector2f pos, Vector2f vel, float lifetime);
private:
	
	// desc: utility to remove a bullet at index (performs swap operation)
	// precond: not empty
	// note: this will cause elements to be skipped if forward iterating
	void removeBullet(int index);

	// desc: contains current bullets
	std::vector<Bullet> bullets;
};