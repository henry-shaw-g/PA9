/*
	file: BodySystem.h
	desc: 
		- class for managing bodies in a scene
		- might need to make a spatial query data structure if we take the bullet hell route
		- body oddy oddy oddy
*/
#pragma once

#include <vector>

#include "Body.h"

typedef unsigned int uint;

class BodySystem {
public:
	// ctor: default
	BodySystem();

	// desc: run a body update
	// args: (float) dt, timestep (time between frames, how much we should step the simulation forward), in seconds btw
	void update(float dt);

	// desc: adds a body the list of dynamic bodies (moving, do collide)
	void addBody(Body& body);

	// desc: removes the body from the list (the id needs to be maintained for this to work)
	void removeBody(Body& body);

private:
	
	bool invalidBodyIndex(uint index);

	std::vector<Body*> dynamicBodies; // this system is very unsafe

};
