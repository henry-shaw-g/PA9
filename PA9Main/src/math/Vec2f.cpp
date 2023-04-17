/*
	file: Vec2f.cpp
	desc: implements the utility 2d vector class
*/

#include <cmath>

#include "Vec2.h"

Vec2f::Vec2f() : sf::Vector2f() {};

Vec2f::Vec2f(float x, float y) : sf::Vector2f(x, y) {};

Vec2f::Vec2f(const Vec2f& copy) 
{
	*this = copy; // invoke copy assignment operator
}

Vec2f::Vec2f(const sf::Vector2f& copy)
{
	*this = copy;
}

Vec2f& Vec2f::operator= (const Vec2f& lhs) 
{
	x = lhs.x;
	y = lhs.y;
	return *this;
}

Vec2f& Vec2f::operator= (const sf::Vector2f& lhs) {
	x = lhs.x;
	y = lhs.y;
	return *this;
}

float Vec2f::mag() const
{
	return sqrtf(x * x + y * y);
}

Vec2f Vec2f::norm() const
{
	return *this / mag();
}

float Vec2f::dot(const Vec2f& lhs) const
{
	return x * lhs.x + y * lhs.y;
}

Vec2f Vec2f::rcross() const
{
	return Vec2f(y, -x);
}

Vec2f Vec2f::lcross() const
{
	return Vec2f(-y, x);
}