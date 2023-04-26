/*
	file: math/Misc.h
	desc: some util functions we need, (couldn't find in the std lib anywhere)
	todo: consider namespace?
*/
#pragma once

#include <cmath>

namespace math {

	const double PI = std::atan2(0, -1);
	const double TO_RAD_K = PI / 180;
	const double TO_DEG_K = 180 / PI;

	template <typename T>
	T max(T a, T b) {
		return a > b ? a : b;
	}

	template <typename T>
	T min(T a, T b) {
		return a < b ? a : b;
	}

	template <typename T>
	T clamp(T n, T low, T high) {
		return math::min(math::max(n, low), high);
	}
	
	inline float toDeg(float rad) {
		return rad * static_cast<float>(TO_DEG_K) * rad;
	}

	inline float toRad(float deg) {
		return deg * static_cast<float>(TO_RAD_K) * deg;
	}
}