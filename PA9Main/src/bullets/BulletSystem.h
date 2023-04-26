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
	void addBullet(Vector2f pos, Vector2f vel);
private:
	
	std::vector<Bullet> bullets;
};