/*
	file: Vec2f.cpp
	desc: implements the utility 2d vector class
*/

#include <iomanip>
#include <cmath>

#include "Vec2.h"

const Vec2f Vec2f::Zero(0, 0); // define the zero static member

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

std::ostream& operator << (std::ostream& lhs, const Vec2f& rhs) {
	lhs << std::setprecision(4) << rhs.x << ", " << rhs.y;
	return lhs;
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