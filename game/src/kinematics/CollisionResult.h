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
	Vector2f point = Vec2::Zero; // roughly the point of contact
	Vector2f offset = Vec2::Zero; // encodes the pushback direction and distance

	void debug_draw(sf::RenderTarget& renderTarget) {
		sf::CircleShape circle(3.0f, 8);
		circle.setFillColor(sf::Color::Green);
		circle.setOrigin(circle.getRadius(), circle.getRadius());
		circle.setPosition(point);
		renderTarget.draw(circle);
	}
};
