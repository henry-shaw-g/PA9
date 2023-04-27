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

std::ostream& operator<<(std::ostream& lhs, const Vector2f& rhs)
{
	lhs << std::setprecision(4) << rhs.x << ", " << rhs.y;
	return lhs;
}