/*
	file: BodySystem.h
	desc: 
		- class for managing bodies in a scene
		- might need to make a spatial query data structure if we take the bullet hell route
		- body oddy oddy oddy
*/
#pragma once

#include <vector>

#include "SFML/Graphics.hpp"

#include "CollisionResult.h"
#include "LineCastResult.h"
#include "Body.h"
#include "CircleBody.h"
#include "AxisBoxBody.h"

typedef unsigned int uint;

class KinematicsTests; // forward declare for the testing class

class BodySystem {
public:
	friend KinematicsTests;

	// ctor: default
	BodySystem();

	// desc: run a body update
	// args: (float) dt, timestep (time between frames, how much we should step the simulation forward), in seconds btw
	void update(float dt);

	// desc: adds a body the list of dynamic bodies (moving, do collide)
	void addBody(Body& body);

	// desc: removes the body from the list (the id needs to be maintained for this to work)
	void removeBody(Body& body);

	// desc: find nearest intersection against a body / tile in system
	LineCastResult lineCast(Vec2f p0, Vec2f p1);

	// desc: draw bodies as wireframes for debugging
	void debug_drawBodies(sf::RenderTarget& renderTarget);

	// desc: draw collisions for debugging
	void debug_drawCollisions(sf::RenderTarget& renderTarget);

	// desc: draw linecast intersections for debugging
	void debug_drawLineCasts(sf::RenderTarget& renderTarget);
private:
	
	// desc: get collision info for two circles colliding
	// precond: b1 and b2 are unique
	CollisionResult checkCircleCircleCollide(const CircleBody& b1, const CircleBody& b2);

	// desc: get collision for a circle and a tile box colliding
	CollisionResult checkCircleAxisBoxCollide(const CircleBody& b1, const AxisBoxBody& b2);

	// desc: get line cast result on a circle:
	LineCastResult checkCircleLineCast(const CircleBody& body, Vec2f p0, Vec2f p1) const;
	
	// desc: get line cast result on an AABB:
	LineCastResult checkAxisBoxLineCast(const AxisBoxBody& body, Vec2f p0, Vec2f p1) const;

	bool invalidBodyIndex(uint index);

	std::vector<Body*> dynamicBodies; // this system is very unsafe
	std::vector<CollisionResult> debug_collisions;
	std::vector<LineCastResult> debug_lineCasts;
	// TEMP
	AxisBoxBody testBox = AxisBoxBody::fromTile(3, 3, 50, 50);
};
