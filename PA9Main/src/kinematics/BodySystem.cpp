/*
	file: BodySystem.cpp
	desc: implements the BodySystem class
*/

#include <cmath>

#include "SFML/System.hpp"

#include "../math/Vec2.h"
#include "BodySystem.h"

static const float FCOMPARE_EPSILON = 0.0001; // might need this to be smaller
static const float PUSHBACK_EPSILON = 0.01; // an extra nudge so floating point doesn't think the colliders are still colliding (may be unstable?)

/* UTILITY */

// returns -1 if no solution

// fuzzy equality check for float against 0
inline bool fequal (float n) {
	return n * n < FCOMPARE_EPSILON;
}

// fuzzy equality check for floats a & b
inline bool fequal(float a, float b) {
	return (a - b) * (a - b) < FCOMPARE_EPSILON;
}

inline static float solveAlignedIntersect(float xt, float dx) {
	if (fequal(dx)) {
		// since we are checking against segment, only care about ranges from 0 to 1
		return 2.f; 
	}
	else {
		return xt / dx;
	}
}

/* BODY SYSTEM */

BodySystem::BodySystem() {}

void BodySystem::update(float dt) {
	// clear last step's collision records
	debug_collisions.clear();

	// integrate positions from velocity
	{
		for (int i = 0; i < dynamicBodies.size(); ++i) {
			Body& b = *dynamicBodies[i];
			Vector2f p0 = b.getPosition();
			Vector2f v = b.velocity;
			Vector2f p1 = p0 + v * dt;
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
				}

				if (result.collided) {
					// for 2 dynamic objects, both get moved
					b1.resolveCollision(result.offset * 0.5f);
					b2.resolveCollision(-result.offset * 0.5f);
					// record collision for debugging (maybe other purposes?)
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
				/*if (result.collided) {
					resolveCircleAxisBoxCollide(c1, tileBody, result);
				}*/
			}

			if (result.collided) {
				b1.resolveCollision(result.offset);
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

LineCastResult BodySystem::lineCast(Vector2f p0, Vector2f p1) {
	LineCastResult result;

	result = checkAxisBoxLineCast(testBox, p0, p1);
	debug_lineCasts.push_back(result);
	

	return result;
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
	//debug_collisions.clear();
}

void BodySystem::debug_drawLineCasts(sf::RenderTarget& renderTarget) {
	LineCastResult result;
	while (!debug_lineCasts.empty()) {
		result = debug_lineCasts.back();
		debug_lineCasts.pop_back();
		result.debug_draw(renderTarget);
	}
}

CollisionResult BodySystem::checkCircleCircleCollide(const CircleBody& b1, const CircleBody& b2) {
	CollisionResult result;
	Vector2f r = b2.getPosition() - b1.getPosition();
	float d12 = b1.radius + b2.radius;
	if (Vec2::dot(r, r) < d12 * d12) {
		result.collided = true;
		float d = Vec2::mag(r);
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

CollisionResult BodySystem::checkCircleAxisBoxCollide(const CircleBody& b1, const AxisBoxBody& b2) {
	CollisionResult result;

	float abW = b2.getWidth();
	float abH = b2.getHeight();
	float cR = b1.radius;

	Vector2f r0 = b1.getPosition() - b2.getPosition();
	Vector2f close = Vector2f(
		std::fmin(std::fmax(r0.x, -abW * 0.5f), abW * 0.5f),
		std::fmin(std::fmax(r0.y, -abH * 0.5f), abH * 0.5f)
	);
	Vector2f r1 = close - r0;

	if (Vec2::dot(r1, r1) < cR * cR) {
		result.collided = true;
		float d = Vec2::mag(r1);
		float o = cR - d;
		result.offset = r1 / d * o;
		result.point = close + b2.getPosition();
	}
	else {
		result.collided = false;
	}

	return result;
}

LineCastResult BodySystem::checkCircleLineCast(const CircleBody& body, Vector2f p0, Vector2f p1) const {
	// do a bunch of projections to find nearest point on line to circle
	Vector2f u = p1 - p0;
	Vector2f v = body.getPosition() - p0;
	Vector2f w = v * (Vec2::dot(u, v) / Vec2::dot(u, u));
	Vector2f o = u - w;

	LineCastResult result;
	// check radius and get intersection point
	if (Vec2::dot(u, v) < body.radius * body.radius) {
		result.intersection = true;
		float d = sqrt(body.radius * body.radius + Vec2::dot(o, o));
		Vector2f p = d * Vec2::norm(u);
		Vector2f huh = w - (p)+p0;
		result.point = huh;
		result.normal = result.point - body.getPosition();
	}
	else {
		result.intersection = false;
	}
	return result;
}

static float lineCast_solveAxisBoxSide(float r1, float r2, float s1, float a, float b) {
	if (fequal(r1)) {
		return -1.f;
	}
	float t = s1 / r1;
	float s2 = t * r2;
	return (a < s2 && s2 < b) ? t : -1.f;
}

LineCastResult BodySystem::checkAxisBoxLineCast(const AxisBoxBody& body, Vector2f p0, Vector2f p1) const {
	// parameter which we will solve for against every plane of the axis box
	float tmin = 2.f; // the maximum value we care about is 1 so this is fine
	float t;
	Vector2f r = p1 - p0;
	float left = body.getLeft() - p0.x, top = body.getTop() - p0.y, 
		right = body.getRight() - p0.x, bottom = body.getBottom() - p0.y;

	t = lineCast_solveAxisBoxSide(r.x, r.y, left, top, bottom);
	tmin = (t > 0.f && t < tmin) ? t : tmin;
	t = lineCast_solveAxisBoxSide(r.x, r.y, right, top, bottom);
	tmin = (t > 0.f && t < tmin) ? t : tmin;
	t = lineCast_solveAxisBoxSide(r.y, r.x, top, left, right);
	tmin = (t > 0.f && t < tmin) ? t : tmin;
	t = lineCast_solveAxisBoxSide(r.y, r.x, bottom, left, right);
	tmin = (t > 0.f && t < tmin) ? t : tmin;

	LineCastResult result;
	result.p0 = p0, result.p1 = p1;

	if (tmin > 0.f && tmin < 1.f) {
		result.intersection = true;
		result.point = p0 + r * tmin;
		result.t = tmin;
		// todo: find least dumb way to get normal (could do it w/ branch hell, but nah)
	}
	else {
		result.intersection = false;
	}

	return result;
}