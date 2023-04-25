/*
	file: math/Misc.h
	desc: some util functions we need, (couldn't find in the std lib anywhere)
	todo: consider namespace?
*/
#pragma once

namespace math {

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
	
}