/*
	file: Config.h
	desc: 
		- just throw general configs in here for now (like windowing stuff)
		- note: everything must be constant
		- note: also we shouldn't use references to this data since its not being externed so will probably exist simultaneously in all TUs?

*/
#pragma once

namespace GameConfig {
	// the size of the window in actual screen units (presumably pixels?)
	const unsigned int WINDOW_REAL_W = 960;
	const unsigned int WINDOW_REAL_H = 540;
	// the size of the viewport we are rendering within the window (if we are going for pixel art this should probably be like 1 view pixel / 2 real pixels)
	const unsigned int WINDOW_VIEW_W = 480;
	const unsigned int WINDOW_VIEW_H = 270;
}