/*
	file: TestKinematics.h
*/
#pragma once

#include <vector>
#include "SFML/Graphics.hpp"
#include "math/Vec2.h"

typedef unsigned int uint;

class BallCollider {
public:
	Vec2f _pos;
	Vec2f _vel;
	float _rad{ 0.f };
};

class StaticCollision {
public:
	Vec2f _dir;
	float _dist{ 0.f };
	Vec2f _point; // mostly for debug info
};

class AABBCollider : public sf::FloatRect {
public:
	Vec2f _vel;
	
	static AABBCollider fromTile(uint row, uint col, float w, float h);
};

class Tile {
public:
	enum Type {
		Empty = 0 << 0,
		Solid = 1 << 0,
	};

	Tile(Type type = Empty);

	Type type();
	bool debug_collideCheck();
	void debug_collideCheck(bool checked);

private:
	uint _field = 0;
};

class TestKinematics {
public:
	void init();
	void update(float dt);
	void draw(sf::RenderTarget& renderTarget);
private:
	// ball objects
	std::vector<BallCollider> _balls;

	// tiles (we can do some spatial detection for this?)
	uint _tileCols = 10;
	uint _tileRows = 10;
	uint _tileW = 10;
	uint _tileH = 10;
	Tile _tiles[10][10]; // i think this initializes all to empty?

	std::vector<StaticCollision> _collisions;

	void collideBallTiles(BallCollider& ball);
};