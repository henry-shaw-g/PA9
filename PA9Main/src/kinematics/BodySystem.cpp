/*
	file: BodySystem.cpp
	desc: implements the BodySystem class
*/

#include <cmath>

#include "BodySystem.h"

static const float PUSHBACK_EPSILON = 0.01; // an extra nudge so floating point doesn't think the colliders are still colliding (may be unstable?)

// BODY SYSTEM IMPL

BodySystem::BodySystem() {}

void BodySystem::update(float dt) {
	// clear last step's collision records
	debug_collisions.clear();

	// integrate positions from velocity
	{
		for (int i = 0; i < dynamicBodies.size(); ++i) {
			Body& b = *dynamicBodies[i];
			Vec2f p0 = b.getPosition();
			Vec2f v = b.velocity;
			Vec2f p1 = p0 + v * dt;
			b.setPosition(p1);
		}
	}

	// detect and resolve dynamic-dynamic collisions O(n^2) approach
	{
		CollisionResult result;
		for (int i = 0; i < dynamicBodies.size(); ++i) {
			Body& b1 = *dynamicBodies[i];
			BodyType type1 = b1.getType();
			if (type1 == BodyType::Point)
				continue;

			result.collided = false;
			for (int j = 0; j < dynamicBodies.size(); ++j) {
				if (j == i) // don't do check on current
					continue;
				Body& b2 = *dynamicBodies[j];
				BodyType type2 = b1.getType();
				if (type2 == BodyType::Point)
					continue;

				uint typeMask = (uint)type1 | (uint)type2;
				if (typeMask == (uint)BodyType::Circle) {
					CircleBody& c1 = static_cast<CircleBody&>(b1), & c2 = static_cast<CircleBody&>(b2);
					result = checkCircleCircleCollide(c1, c2);
					if (result.collided) {
						resolveCircleCircleCollide(c1, c2, result);
					}
				}

				if (result.collided) {
					debug_collisions.push_back(result);
				}
			}
		}
	}

	// detect and resolve dynamic-static(tiles) collisions
	{
		CollisionResult result;
		for (int i = 0; i < dynamicBodies.size(); ++i) {
			// TEMP: check against the tiles
			Body& b1 = *dynamicBodies[i];
			AxisBoxBody& tileBody = testBox;

			if (b1.getType() == BodyType::Circle) {
				CircleBody& c1 = static_cast<CircleBody&>(b1);
				result = checkCircleAxisBoxCollide(c1, tileBody);
				if (result.collided) {
					resolveCircleAxisBoxCollide(c1, tileBody, result);
				}
			}

			if (result.collided) {
				debug_collisions.push_back(result);
			}
		}
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

void BodySystem::debug_drawBodies(sf::RenderTarget& renderTarget) {
	for (int i = 0; i < dynamicBodies.size(); ++i) {
		Body& b = *dynamicBodies[i];
		b.debug_draw(renderTarget);
	}

	// TEMP
	testBox.debug_draw(renderTarget);
}

void BodySystem::debug_drawCollisions(sf::RenderTarget& renderTarget) {
	CollisionResult result;
	while (!debug_collisions.empty()) {
		result = debug_collisions.back();
		debug_collisions.pop_back();
		result.debug_draw(renderTarget);
	}
	// jic:
	debug_collisions.clear();
}

CollisionResult BodySystem::checkCircleCircleCollide(const CircleBody& b1, const CircleBody& b2) {
	CollisionResult result;
	Vec2f r = b2.getPosition() - b1.getPosition();
	float d12 = b1.radius + b2.radius;
	if (r.dot(r) < d12 * d12) {
		result.collided = true;
		float d = r.mag();
		float o = d12 - d; // intersection depth between circle surface
		float m1 = b1.radius - o / 2; // distance from intersection midpoint and b1 surface
		result.offset = r / d * (o + PUSHBACK_EPSILON);
		result.point = r / d * m1 + b1.getPosition();
	}
	else {
		result.collided = false;
	}

	return result;
}

void BodySystem::resolveCircleCircleCollide(CircleBody& b1, CircleBody& b2, CollisionResult collision) {
	// push the first circle away from the the collision
	Vec2f b1Pos = b1.getPosition();
	b1.setPosition(b1Pos - collision.offset * 0.5f);
	// push the second circle away from the collison
	Vec2f b2Pos = b2.getPosition();
	b2.setPosition(b2Pos +  collision.offset * 0.5f);
}

CollisionResult BodySystem::checkCircleAxisBoxCollide(const CircleBody& b1, const AxisBoxBody& b2) {
	CollisionResult result;

	float abW = b2.getWidth();
	float abH = b2.getHeight();
	float cR = b1.radius;

	Vec2f r0 = b1.getPosition() - b2.getPosition();
	Vec2f close = Vec2f(
		std::fmin(std::fmax(r0.x, -abW * 0.5f), abW * 0.5f),
		std::fmin(std::fmax(r0.y, -abH * 0.5f), abH * 0.5f)
	);
	Vec2f r1 = close - r0;

	if (r1.dot(r1) < cR * cR) {
		result.collided = true;
		float d = r1.mag();
		float o = cR - d;
		result.offset = r1 / d * o;
		result.point = close + b2.getPosition();
	}
	else {
		result.collided = false;
	}

	return result;
}

void BodySystem::resolveCircleAxisBoxCollide(CircleBody& b1, AxisBoxBody& _, CollisionResult collision) {
	Vec2f b1Pos = b1.getPosition();
	b1.setPosition(b1Pos - collision.offset);
}