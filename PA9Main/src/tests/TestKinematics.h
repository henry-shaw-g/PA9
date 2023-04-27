/*
	file: TestKinematics.h
	desc: tests for the kinematics features
	note: header only
*/
#pragma once

#include <memory>

#include "../math/Vec2.h"
#include "../Map.h"
#include "../kinematics/BodySystem.h"

namespace Tests {
	class Kinematics {
		public:
			void testLineCastWithTiles() {
				std::cout << "TEST: line cast with tiles:\n";
				std::unique_ptr<Map> map = std::make_unique<Map>();
				map->getTile(1, 1).setWall();
				BodySystem bodySystem(*map);
				LineCastResult result; 
				// test coming from left
				result = bodySystem.lineCast(Vector2f(0, 0), Vector2f(20, 20));
				std::cout << "intersection?: " << result.intersected() << '\n';
				std::cout << "is tile type?: " << (result.type == LineCastResult::Tile) << '\n';
				std::cout << "tile hit: col: " << (result.tileResult.col) << ", row: " << (result.tileResult.row) << '\n';
				std::cout << "normal:" << result.data.normal << '\n';
				// test coming from upper-right
				result = bodySystem.lineCast(Vector2f(37.5, 7.5), Vector2f(22.5, 22.5));
				std::cout << "intersection?: " << result.intersected() << '\n';
				std::cout << "is tile type?: " << (result.type == LineCastResult::Tile) << '\n';
				std::cout << "tile hit: col: " << (result.tileResult.col) << ", row: " << (result.tileResult.row) << '\n';
				std::cout << "normal:" << result.data.normal << '\n';
 			}

			void testLineCastWithBodies() {
				std::cout << "TEST: line cast with bodies:\n";
				std::unique_ptr<Map> map = std::make_unique<Map>();
				BodySystem bodySystem(*map);
				LineCastResult result;
				CircleBody body(Vector2f(20, 20), 5);
				bodySystem.addBody(body);

				result = bodySystem.lineCast(Vector2f(0, 0), Vector2f(20, 20));
				std::cout << "intersecton?: " << result.intersected() << '\n';
				std::cout << "is body type?: " << (result.type == LineCastResult::Body) << '\n';
				std::cout << "pos: " << (result.data.point) << '\n';

			}
	};
}