/*
	file: LineCastResult.h
	desc: describe result of line cast
*/

#pragma once

#include "SFML/Graphics.hpp"

#include "../math/Vec2.h"

class LineCastResult {
public:
	float t; // record this so we can choose minimum result if casting over many
	bool intersection = false;
	Vector2f p0 = Vec2::Zero;
	Vector2f p1 = Vec2::Zero;
	Vector2f point = Vec2::Zero; // point of intersection between ray and 
	Vector2f normal = Vec2::Zero; // normal of the surface at the point of intersection (may use for bouncing bullets?)

	void debug_draw(sf::RenderTarget& renderTarget) const {
		sf::CircleShape circle(3.0f, 8);
		circle.setFillColor(sf::Color::Green);
		circle.setOrigin(circle.getRadius(), circle.getRadius());
		circle.setPosition(point);

		sf::Vertex line[2];
		line[0].position = p0;
		line[0].color = sf::Color::Red;
		line[1].position = p1;
		line[1].color = sf::Color::Red;
		renderTarget.draw(line, 2, sf::LineStrip);

		if (intersection) {
			renderTarget.draw(circle);
		}
	}
};