/*
	file: TestMain.h
	desc: driver for the tests
	note: header only
*/
#pragma once

#include "TestKinematics.h"

namespace Tests {
	inline void run() {
		Tests::Kinematics kinematicsTest;
		kinematicsTest.testLineCast();
	}
}