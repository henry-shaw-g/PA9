/*
	file: BodySystem.h
	desc: 
		- handles managing bodies and collisions
		- needs dependency injection for the tile system
*/
#pragma once

#include <vector>

#include "SFML/Graphics.hpp"

#include "../Map.h"
#include "CollisionResult.h"
#include "LineCastResult.h"
#include "Body.h"
#include "CircleBody.h"
#include "AxisBoxBody.h"

class BodySystem {
public:
	// ctor:
	BodySystem(Map& systemMap);

	// desc: run a body update
	// args: (float) dt, timestep (time between frames, how much we should step the simulation forward), in seconds btw
	void update(float dt);

	// desc: adds a body the list of dynamic bodies (moving, do collide)
	void addBody(Body& body);

	// desc: removes the body from the list (the id needs to be maintained for this to work)
	void removeBody(Body& body);

	// desc: find nearest intersection against a body / tile in system
	LineCastResult lineCast(Vector2f p0, Vector2f p1);

	// desc: draw bodies as wireframes for debugging
	void debug_drawBodies(sf::RenderTarget& renderTarget);

	// desc: draw collisions for debugging
	void debug_drawCollisions(sf::RenderTarget& renderTarget);

	// desc: draw linecast intersections for debugging
	void debug_drawLineCasts(sf::RenderTarget& renderTarget);

private:
	// desc: update the movement of bodies (move their positions according to the velocities & timesteps)
	//	- using the 'integrate' convention since this is like a numerical integration of position
	void integrateBodies(float dt);

	// desc: detect and resolve collisions between the dynamic bodies (only tanks for now)
	void updateBodyCollisions();

	// desc: detect and resolve collisions between the dynamic bodies and the tiles
	void updateTileCollisions();

	// desc: detect and resolve collisions with tiles for 1 body
	void handleTileBodyCollision(Body& b);

	// desc: get collision info for two circles colliding
	// precond: b1 and b2 are unique
	CollisionResult checkCircleCircleCollide(const CircleBody& b1, const CircleBody& b2);

	// desc: get collision for a circle and a tile box colliding
	CollisionResult checkCircleAxisBoxCollide(const CircleBody& b1, const AxisBoxBody& b2);

	// desc: get line cast result on a circle:
	LineCastData checkCircleLineCast(const CircleBody& body, Vector2f p0, Vector2f p1) const;
	
	// desc: get line cast result through tiles:
	LineCastData checkTilesLineCast(Vector2f p0, Vector2f p1, Vector2i& tilePos) const;

	// desc: get line cast result on an AABB:
	LineCastData checkAxisBoxLineCast(const AxisBoxBody& body, Vector2f p0, Vector2f p1) const;

	// desc: utility to produce session unique ids for body
	int generateBodyId();

	// desc: temp procedure to prevent adding duplicate bodies
	bool invalidBodyIndex(int index);

	Map& mapRef; // aggregation reference to the tiles for the game (the Tiles must outlive lifetime of BodySystem)
	std::vector<Body*> dynamicBodies; // this system is very unsafe
	std::vector<CollisionResult> debug_collisions;
	std::vector<LineCastData> debug_lineCasts;
	int idRegister; // counter which we will use to assign 'ids' to the bodies (not, consider -1 invalid / unregistered)
};
