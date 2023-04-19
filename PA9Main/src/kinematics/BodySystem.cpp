/*
	file: BodySystem.cpp
	desc: implements the BodySystem class
*/

#include "BodySystem.h"

// BODY SYSTEM IMPL

BodySystem::BodySystem() {}

void BodySystem::update(float dt) {
	// integrate positions from velocity
	Body* bPtr;
	for (int i = 0; i < dynamicBodies.size(); ++i) {
		bPtr = dynamicBodies[i];
		Body& b = *bPtr;
		Vec2f p0 = b.position;
		Vec2f v = b.velocity;
		Vec2f p1 = p0 + v * dt;
		b.position = p1;
	}
}

void BodySystem::addBody(Body& body)
{
	// this kind of enforces duplicate pointers to bodies not being in the system
	if (!invalidBodyIndex(body.getIndex()))
		return;

	uint index = dynamicBodies.size();
	body.setIndex(index);
	dynamicBodies.push_back(&body);
}

void BodySystem::removeBody(Body& body)
{
	uint index = body.getIndex();
	// make sure we aren't messing up due to a body not actually being in the list
	if (invalidBodyIndex(index))
		return; 
	// to keep the bodies vector contiguous, am swapping the last element with whatever we remove
	// then popping the back
	dynamicBodies[index] = dynamicBodies.back(); 
	dynamicBodies.pop_back();
	
	// mark the body as not being in a list just in case
	body.setIndex(-1);
}

bool BodySystem::invalidBodyIndex(uint index) {
	return index == -1;
	// todo: possible bounds checking
}