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
	Vec2f p0 = Vec2f::Zero;
	Vec2f p1 = Vec2f::Zero;
	Vec2f point = Vec2f::Zero; // point of intersection between ray and 
	Vec2f normal = Vec2f::Zero; // normal of the surface at the point of intersection (may use for bouncing bullets?)

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