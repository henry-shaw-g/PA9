/*
	file: CircleBody.h
	desc: encapsulates position and collision data for circular bodies
*/
#pragma once

#include "../math/Vec2.h"
#include "Body.h"

class CircleBody : public Body {
public:
	CircleBody(Vector2f pos, float newRadius) :
		Body(pos), radius(newRadius) {}

	float radius = 0.f;

	// desc: set radius of the circle
	float getRadius() { return radius; }

	// desc: get radius of the circle
	void setRadius(float newRadius) { radius = newRadius; }

	// desc: draw the wireframe of the collider for debugging purposes
	virtual void debug_draw(sf::RenderTarget& renderTarget) const override;

	//desc: get axis aligned bounding box of the circle
	virtual sf::FloatRect getAABB() const override;

	// desc: tell user in polym context that this is a circle (poor design, we know)
	virtual BodyType getType() const override { return BodyType::Circle; }
};