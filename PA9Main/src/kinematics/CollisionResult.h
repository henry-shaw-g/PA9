/*
	file: Collision.h
	desc: contains collision instance information 
*/
#pragma once

#include "SFML/Graphics.hpp"

#include "../math/Vec2.h"

class CollisionResult {
public:
	bool collided = false;
	Vec2f point = Vec2f::Zero; // roughly the point of contact
	Vec2f offset = Vec2f::Zero; // encodes the pushback direction and distance

	void debug_draw(sf::RenderTarget& renderTarget) {
		sf::CircleShape circle(3.0f, 8);
		circle.setFillColor(sf::Color::Yellow);
		circle.setOrigin(circle.getRadius(), circle.getRadius());
		circle.setPosition(point);
		renderTarget.draw(circle);
	}
};
