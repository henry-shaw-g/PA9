#include "Test.h"

void Test::testWrapper() {

	testWalls();
}

void Test::testWalls() {

	Map test;
	int wallCount = 0;

	for (int column = 0; column < 32; ++column) {
		for (int row = 0; row < 18; ++row) {
			if (test.getTile(column, row).isWall()) {
				++wallCount;
			}
		}
	}

	if (wallCount == 60) {
		std::cout << "Walls Generation Successful" << std::endl;
	}

	else {
		std::cout << "Wall Generation Failed" << std::endl;
	}
}