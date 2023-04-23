/*
	file: Vec2f.cpp
	desc: implements the utility 2d vector class
*/

#include <iomanip>
#include <cmath>

#include "Vec2.h"

const float ZERO_EPSILON = 0.0001;

using sf::Vector2f;

const Vector2f Vec2::Zero = Vector2f(0.f, 0.f);
const Vector2f Vec2::I = Vector2f(1.f, 0.f);
const Vector2f Vec2::J = Vector2f(0.f, 1.f);

std::ostream& Vec2::operator<<(std::ostream& lhs, const Vector2f& rhs)
{
	lhs << std::setprecision(4) << rhs.x << ", " << rhs.y;
	return lhs;
}

float Vec2::mag(Vector2f v)
{
	return sqrt(v.x * v.x + v.y * v.y);
}

Vector2f Vec2::norm(Vector2f v)
{
	float m = fmax(Vec2::mag(v), ZERO_EPSILON); // avoid div / zero errors
	return v / m;
}

float Vec2::dot(Vector2f u, Vector2f v)
{
	return u.x * v.x + u.y * v.y;
}

Vector2f Vec2::rcross(Vector2f v)
{
	return Vector2f(v.y, -v.x);
}

Vector2f Vec2::lcross(Vector2f v)
{
	return Vector2f(-v.y, v.x);
}


// OLD Vec2f DERIVED CLASS (DO NOT USE) //

const Vec2f Vec2f::Zero(0, 0); // define the zero static member

Vec2f::Vec2f() : sf::Vector2f() {};

Vec2f::Vec2f(float x, float y) : sf::Vector2f(x, y) {};

Vec2f::Vec2f(const sf::Vector2f& copy)
{
	*this = copy;
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
