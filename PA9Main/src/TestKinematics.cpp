/*
	file: TestKinematics.cpp
	desc: omega spaghetti
*/

#pragma once

#include <iostream>
#include <cmath>

#include "TestKinematics.h"
#include "math/Vec2.h"

///* AABB COLLIDER IMPL */
//AABBCollider AABBCollider::fromTile(uint row, uint col, float w, float h) {
//	AABBCollider aabb;
//	aabb.left = col * w;
//	aabb.top = row * h;
//	aabb.width = w;
//	aabb.height = h;
//	return aabb;
//}
//
///* TILE IMPL */
//Tile::Tile(Tile::Type type) {
//	_field = type;
//}
//
//Tile::Type Tile::type() {
//	return static_cast<Tile::Type>(_field & 0xff);
//}
//
//bool Tile::debug_collideCheck() {
//	return static_cast<bool>(_field & (1 << 17));
//}
//
//void Tile::debug_collideCheck(bool checked) {
//	if (checked)
//		_field |= 1 << 17;
//	else
//		_field &= ~(1 << 17);
//}
//
///* TESTING STUFF */
//
//template <typename T>
//static inline T max(T a, T b) {
//	return b > a ? b : a;
//}
//
//template <typename T>
//static inline T min(T a, T b) {
//	return b < a ? b : a;
//}
//
//static bool checkBallBallCollision(BallCollider& b1, BallCollider& b2, StaticCollision& result) {
//	Vec2f r = b2._pos - b1._pos;
//	if (r.dot(r) < (b1._rad + b2._rad) *(b1._rad + b2._rad)) {
//		result._dist = r.mag();
//		result._dir = r / result._dist;
//		result._point = b1._pos;// for debug:
//		return true;
//	}
//	else {
//		return false;
//	}
//}
//
//static void resolveBallBallCollision(BallCollider& b1, BallCollider& b2, const StaticCollision& result) {
//	float s = b1._rad + b2._rad - result._dist;
//	b1._pos -= result._dir * s * 0.5f;
//	b2._pos += result._dir * s * 0.5f;
//}
//
//static bool checkBallTileCollision(BallCollider& b, AABBCollider& aabb, StaticCollision& result) {
//	// closest point on rect to circle
//	Vec2f pRect(
//		max<float>(aabb.left, min<float>(aabb.left + aabb.width, b._pos.x)),
//		max<float>(aabb.left, min<float>(aabb.top + aabb.height, b._pos.y))
//		);
//	Vec2f r = pRect - b._pos;
//	if (r.dot(r) < b._rad * b._rad) {
//		// collision
//		result._dist = r.mag();
//		result._dir = r / result._dist;
//		result._point = b._pos;
//		return true;
//	}
//
//	return false;
//}
//
//static void resolveBallTileCollision(BallCollider& b, AABBCollider& _, const StaticCollision& result) {
//	b._pos -= result._dir * (b._rad - result._dist);
//}
//
//void TestKinematics::init() 
//{
//	// setup balls
//	BallCollider b1;
//	{
//		b1._pos = Vec2f(10.0f, 10.0f);
//		b1._vel = Vec2f(15.0f, 15.0f);
//		b1._rad = 10.0f;
//		_balls.push_back(b1);
//	}
//	BallCollider b2;
//	{
//		b2._pos = Vec2f(90.0f, 10.0f);
//		b2._vel = Vec2f(-15.0f, 15.0f);
//		b2._rad = 10.0f;
//		_balls.push_back(b2);
//	}
//
//	// setup tiles
//	for (uint r = 0; r < _tileRows - 1; r++) {
//		for (uint c = 0; c < _tileCols; c++) {
//			_tiles[r][c] = Tile(Tile::Empty);
//		}
//	}
//	for (uint c = 0; c < _tileCols; ++c) {
//		_tiles[9][c] = Tile(Tile::Solid);
//	}
//	_tiles[7][4] = Tile(Tile::Solid), _tiles[7][5] = Tile(Tile::Solid);
//}
//
//void TestKinematics::update(float dt) 
//{
//	// update positions
//	for (int i = 0; i < _balls.size(); ++i) {
//		BallCollider& ball = _balls[i];
//		ball._pos += ball._vel * dt;
//	}
//
//	// handle collisions
//	_collisions.clear();
//	StaticCollision collisionResult;
//	for (int i = 0; i < _balls.size(); ++i) {
//		for (int j = 0; j < _balls.size(); ++j) {
//			if (j == i)
//				continue;
//			BallCollider& ball1 = _balls[i], & ball2 = _balls[j];
//			if (checkBallBallCollision(ball1, ball2, collisionResult)) {
//				resolveBallBallCollision(ball1, ball2, collisionResult);
//				_collisions.push_back(collisionResult);
//			}
//		}
//	}
//	for (int i = 0; i < _balls.size(); ++i) {
//		BallCollider& ball = _balls[i];
//		this->collideBallTiles(ball);
//	}
//}
//
//void TestKinematics::draw(sf::RenderTarget& renderTarget)
//{
//	// draw tiles
//	{
//		
//		sf::RectangleShape tileShape;
//		for (uint r = 0; r < _tileRows; ++r) {
//			for (uint c = 0; c < _tileCols; ++c) {
//				bool draw = false;
//				sf::Color tileColor = sf::Color::White;
//				Tile& tile = _tiles[r][c];
//				if (tile.debug_collideCheck()) {
//					tileColor *= sf::Color::Cyan;
//					draw = true;
//				}
//				if (tile.type() == Tile::Solid) {
//					tileColor *=sf::Color::Green;
//					draw = true;
//				}
//
//				if (draw) {
//					tileShape.setSize(Vec2f(_tileW, _tileH));
//					tileShape.setPosition(c * _tileW, r * _tileH);
//					tileShape.setFillColor(tileColor);
//					renderTarget.draw(tileShape);
//				}
//			}
//		}
//	}
//
//	// draw objects
//	for (int i = 0; i < _balls.size(); ++i) {
//		BallCollider& ball = _balls[i];
//		sf::CircleShape ballShape (ball._rad);
//		{
//			ballShape.setFillColor(sf::Color::Transparent);
//			ballShape.setOutlineColor(sf::Color::White);
//			ballShape.setOutlineThickness(1);
//		}
//
//		ballShape.setPosition(ball._pos);
//		ballShape.setOrigin(ball._rad, ball._rad);
//		renderTarget.draw(ballShape);
//	}
//
//	// draw debug
//	sf::Vertex line[2];
//	line[0].color = sf::Color::Red;
//	line[1].color = sf::Color::Red;
//	for (int i = 0; i < _collisions.size(); ++i) {
//		StaticCollision collision = _collisions[i];
//		line[0].position = collision._point;
//		line[1].position = collision._point + collision._dir * collision._dist;
//		renderTarget.draw(line, 2, sf::LineStrip);
//	}
//}
//
//void TestKinematics::collideBallTiles(BallCollider& ball) {
//	float minX = ball._pos.x - ball._rad;
//	float maxX = ball._pos.x + ball._rad;
//	float minY = ball._pos.y - ball._rad;
//	float maxY = ball._pos.y + ball._rad;
//
//	uint minR = max<uint>(floor(minY / _tileH), 0);
//	uint maxR = min<uint>(ceil(maxY / _tileH), _tileRows);
//	uint minC = max<uint>(floor(minX / _tileW), 0);
//	uint maxC = min<uint>(ceil(maxX / _tileW), _tileCols);
//
//	for (uint r = 0; r < _tileCols; ++r) {
//		for (uint c = 0; c < _tileCols; ++c) {
//			Tile& tile = _tiles[r][c];
//			tile.debug_collideCheck(false);
//		}
//	}
//
//	std::cout << ball._pos.x << ", " << ball._pos.y << ": min r:" << minR << " max r: " << maxR << '\n';
//	std::cout << "min c: " << minC << " max c: " << maxC << '\n';
//
//	StaticCollision collisionResult;
//	for (uint r = minR; r < maxR; ++r) {
//		for (uint c = minC; c < maxC; ++c) {
//			Tile& tile = _tiles[r][c];
//			tile.debug_collideCheck(true);
//			if (tile.type() != Tile::Solid)
//				continue;
//
//			AABBCollider tileCollider = AABBCollider::fromTile(r, c, _tileH, _tileW);
//			if (checkBallTileCollision(ball, tileCollider, collisionResult)) {
//				std::cout << "collision at row" << r << " col " << c << '\n';
//				resolveBallTileCollision(ball, tileCollider, collisionResult);
//				_collisions.push_back(collisionResult);
//			}
//		}
//	}
//}