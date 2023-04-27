/*
	file: TestMain.h
	desc: driver for the tests
	note: header only
*/
#pragma once

#include "TestKinematics.h"
#include "TestWalls.h"

namespace Tests {
	inline void run() {
		Tests::Kinematics kinematicsTest;
		kinematicsTest.testLineCastWithTiles();
		kinematicsTest.testLineCastWithBodies();

		Tests::Walls wallsTest;
		wallsTest.testGeneration();
	}
}