/*
	file: BodySystem.cpp
	desc: implements the BodySystem class
*/

#include <cmath>
#include <algorithm>
#include <limits>

#include "SFML/System.hpp"

#include "../math/Vec2.h"
#include "../math/Misc.h"
#include "BodySystem.h"

static const float FCOMPARE_EPSILON = 0.0001f; // might need this to be smaller
static const float PUSHBACK_EPSILON = 0.01f; // an extra nudge so floating point doesn't think the colliders are still colliding (may be unstable?)
static const float NO_INTERSECT = 2.0f;

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

/* BODY SYSTEM */

BodySystem::BodySystem(Map& systemMap) :
	mapRef (systemMap)
{
	idRegister = 0; // set id register to start at 0

}

void BodySystem::update(float dt) {
	// clear last step's collision records
	debug_collisions.clear();

	// integrate positions from velocity
	BodySystem::integrateBodies(dt);

	// detect and resolve dynamic-dynamic collisions O(n^2) approach
	updateBodyCollisions();

	// detect and resolve dynamic-static(tiles) collisions
	updateTileCollisions();
}

void BodySystem::integrateBodies(float dt) {
	for (int i = 0; i < dynamicBodies.size(); ++i) {
		Body& b = *dynamicBodies[i];
		Vector2f p0 = b.getPosition();
		Vector2f v = b.velocity;
		Vector2f p1 = p0 + v * dt;
		b.setPosition(p1);
	}
}

void BodySystem::updateBodyCollisions() {
	using uint = unsigned int;
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
			switch (typeMask) {
				case static_cast<uint>(BodyType::Circle):
					result = checkCircleCircleCollide(
						static_cast<CircleBody&>(b1),
						static_cast<CircleBody&>(b2));
					break;
				default:
					result.collided = false;
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

void BodySystem::updateTileCollisions() {
	CollisionResult result;
	for (int i = 0; i < dynamicBodies.size(); ++i) {
		handleTileBodyCollision(*dynamicBodies[i]);
	}
}

void BodySystem::handleTileBodyCollision(Body& b)
{
	// get the maximum AABB of the body
	sf::FloatRect aabb = b.getAABB();
	// get the maximum rect of coordinates containing the AABB
	Vector2f tileSize = mapRef.tileSize();
	float x0 = std::floor(aabb.left / tileSize.x);
	float x1 = std::ceil((aabb.left + aabb.width) / tileSize.x);
	float y0 = std::floor(aabb.top / tileSize.y);
	float y1 = std::ceil((aabb.top + aabb.height) / tileSize.y);
		
	// limit the rect to be in the tile system grid
	Vector2u gridSize = mapRef.mapSize();
	int col0 = math::clamp((int)x0 - 1, 
		0, (int)gridSize.x - 1); // 0u literal needed so the template func knows what the args are
	int col1 = math::clamp((int)x1, 
		0, (int)gridSize.x - 1);
	int row0 = math::clamp((int)y0 - 1, 
		0, (int)gridSize.y - 1);
	int row1 = math::clamp((int)y1, 
		0, (int)gridSize.y -1);

	// go through each tile and check / resolve collision w/ body
	BodyType bodyType = b.getType();
	AxisBoxBody tileBody;
	CollisionResult result;
	int row, col;
	for (row = row0; row <= row1; ++row) {
		
		for (col = col0; col <= col1; ++col) {
			if (!mapRef.getTile(col, row).isWall())
				continue;
			tileBody = AxisBoxBody::fromTile(col, row, tileSize.x, tileSize.y);
			switch (bodyType) {
				case BodyType::Circle:
					result = checkCircleAxisBoxCollide(static_cast<CircleBody&>(b), tileBody);
					break;
				default:
					result.collided = false;
			}
			if (result.collided) {
				b.resolveCollision(result.offset);
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

	int index = dynamicBodies.size();
	int id = generateBodyId();
	body.setIndex(index);
	body.setId(id);
	dynamicBodies.push_back(&body);
}

void BodySystem::removeBody(Body& body)
{
	int index = body.getIndex();
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

bool BodySystem::invalidBodyIndex(int index) {
	return index == -1;
	// todo: possible bounds checking
}

int BodySystem::generateBodyId() {
	return idRegister++; // return current id and then increment it for next usage (gives us ~2^31 - 1 unique instances for a session) (could get more if we used unsigned)
}

void BodySystem::debug_drawBodies(sf::RenderTarget& renderTarget) {
	for (int i = 0; i < dynamicBodies.size(); ++i) {
		Body& b = *dynamicBodies[i];
		b.debug_draw(renderTarget);
	}
}

void BodySystem::debug_drawCollisions(sf::RenderTarget& renderTarget) {
	CollisionResult result;
	while (!debug_collisions.empty()) {
		result = debug_collisions.back();
		debug_collisions.pop_back();
		result.debug_draw(renderTarget);
	}
}

void BodySystem::debug_drawLineCasts(sf::RenderTarget& renderTarget) {
	while (!debug_lineCasts.empty()) {
		LineCastData& instance = debug_lineCasts.back();
		debug_lineCasts.pop_back();
		instance.debug_draw(renderTarget);
	}
}

LineCastResult BodySystem::lineCast(Vector2f p0, Vector2f p1) {
	LineCastData castData, minCastData;
	minCastData.t = NO_INTERSECT; // 1 is maximum value we consider so
	LineCastResult result;
	result.type = LineCastResult::None;
	
	// check against bodies
	{
		int minBodyId = -1;
		for (int i = 0; i < dynamicBodies.size(); ++i) {
			Body& b = *dynamicBodies[i];
			switch (b.getType()) {
			case BodyType::Circle:
				castData = checkCircleLineCast(static_cast<CircleBody&>(b), p0, p1);
				break;
			default:
				castData.t = NO_INTERSECT;
				break;
			}

			if (castData.t < minCastData.t) {
				minCastData = castData;
				minBodyId = b.getId();
			}
		}
		if (minCastData.intersected()) {
			result.type = LineCastResult::Body;
			result.data = minCastData;
			result.bodyResult.id = minBodyId;
		}
	}

	// check against tiles:
	{
		sf::Vector2i tile;
		castData = checkTilesLineCast(p0, p1, tile);
		if (castData.t < minCastData.t && castData.intersected()) {
			result.type = LineCastResult::Tile;
			result.data = castData;
			result.tileResult.col = tile.x, result.tileResult.row = tile.y;
		}

	}

	return result;
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

LineCastData BodySystem::checkCircleLineCast(const CircleBody& body, Vector2f p0, Vector2f p1) const {
	// do a bunch of projections to find nearest point on line to circle
	Vector2f u = p1 - p0;
	Vector2f v = body.getPosition() - p0;
	Vector2f w = u * (Vec2::dot(u, v) / Vec2::dot(u, u));
	Vector2f o = v - w;

	LineCastData result;
	result.p0 = p0, result.p1 = p1;

	// check radius to see if intersecting
	if (Vec2::dot(o, o) < body.radius * body.radius) {
		float d_mag = sqrt(body.radius * body.radius - Vec2::dot(o, o));
		Vector2f i = w - Vec2::norm(u) * d_mag;
		float t = Vec2::dot(i, u) / Vec2::dot(u, u);
		result.t = t;
		result.point = i + p0;
		result.normal = result.point - body.getPosition();
	}
	else {
		result.t = NO_INTERSECT;
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

LineCastData BodySystem::checkAxisBoxLineCast(const AxisBoxBody& body, Vector2f p0, Vector2f p1) const {
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

	LineCastData result;
	result.p0 = p0, result.p1 = p1;

	if (tmin > 0.f && tmin < 1.f) {
		result.point = p0 + r * tmin;
		result.t = tmin;
		// todo: find least dumb way to get normal (could do it w/ branch hell, but nah)
	}
	else {
		result.t = NO_INTERSECT;
	}

	return result;
}

// implements DDA algorithm: https://www.youtube.com/watch?v=NbSee-XM7WA&ab_channel=javidx9
// note: last argument is an out param to get the tile hit (garbage if linecastdata is non intersecting)
LineCastData BodySystem::checkTilesLineCast(Vector2f p0, Vector2f p1, Vector2i& posT) const {
	LineCastData result;
	result.p0 = p0, result.p1 = p1;
	
	Vector2f r = p1 - p0;
	float m = Vec2::mag(r);
	
	Vector2u sizeG = mapRef.mapSize(); // tile position, direction of tile change (per axis given direction r)
	Vector2f sizeT = mapRef.tileSize();
	posT.x = (int)(p0.x / sizeT.x);
	posT.y = (int)(p0.y / sizeT.y);
	Vector2i stepT;
	stepT.x = (r.x >= 0.f) ? 1 : -1;
	stepT.y = (r.y >= 0.f) ? 1 : -1;

	Vector2f ds; // change in length w/ respect to each axis
	ds.x = ((r.x == 0.f) ? std::numeric_limits<float>::max() : sqrt(1 + r.y / r.x * r.y / r.x)) / m;
	ds.y = ((r.y == 0.f) ? std::numeric_limits<float>::max() : sqrt(1 + r.x / r.y * r.x / r.y)) / m;
	Vector2f s = Vec2::Zero; // traversed length, w/ respect to each axis
	float sLast = 0;
	// get initial traversals (to next tiles)
	if (stepT.x > 0) {
		s.x = ds.x * ((posT.x + 1) * sizeT.x - p0.x);
	}
	else {
		s.x = ds.x * (p0.x - posT.x * sizeT.x);
	}
	if (stepT.y > 0) {
		s.y = ds.y * ((posT.y + 1) * sizeT.y - p0.y);
	}
	else {
		s.y = ds.y * (p0.y - posT.y * sizeT.y);
	}
	

	Vector2f stepNorm;
	bool inWall = false;
	while (sLast <= 1 && !inWall) {
		std::cout << "col: " << posT.x << ", row: " << posT.y << '\n';
		if (s.x < s.y) {
			posT.x += stepT.x;
			sLast = s.x;
			s.x += ds.x * sizeT.x;
			stepNorm = Vector2f((float)-stepT.x, 0);
		}
		else {
			posT.y += stepT.y;
			sLast = s.y;
			s.y += ds.y * sizeT.y;
			stepNorm = Vector2f(0, (float)-stepT.y);
		}
		if (posT.x < 0 || posT.x >= sizeG.x || posT.y < 0 || posT.y > sizeG.y)
			continue;
		if (sLast <= 1 && mapRef.getTile(posT.x, posT.y).isWall()) {
			inWall = true;
		}
	}

	if (inWall) {
		result.t = sLast;
		result.normal = stepNorm;
		result.point = result.t * r + p0;
	}
	else {
		result.t = NO_INTERSECT;
	}

	return result;
}