#define _USE_MATH_DEFINES
#include <math.h>

#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>

#include "SFML/Window.hpp"
#include "SFML/System.hpp"

#include "kinematics/Body.h"
#include "kinematics/CircleBody.h"
#include "kinematics/BodySystem.h"
#include "bullets/BulletSystem.h"
#include "Tank.h"
#include "resources/ResourceManager.h"
#include "Map.h"

#include "tests/TestMain.h"

void updateTanks(Tank& tank1, Tank& tank2, float dt);
#if 1
int main() {
	Tests::run();
}
#else
int main(void) {
	// setup resources
	ResourceManager::load();
	ResourceManager& gameResourceManager = ResourceManager::service();

	// setup sf window
	sf::RenderWindow window(sf::VideoMode(1440, 810), "WINDOW");
	sf::Event event;
	{
		window.setFramerateLimit(120);
		sf::FloatRect view(0.f, 0.f, 480, 270);
		window.setView(sf::View(view));
	}
	
	// testing texture manager
	sf::Sprite sprite;
	{
		sprite.setTexture(gameResourceManager.getTextureRef("smiley_face_0"));
		sprite.setOrigin(sf::Vector2f(32.0f, 32.0f));
		sprite.setPosition(sf::Vector2f(500.f / 4 / 2, 500.f / 4 / 2));
	}
	
	// testing font manager
	sf::Text textObj("what", gameResourceManager.getFontRef("freecam_font"), 10);
	{
		textObj.setOrigin(textObj.getGlobalBounds().width / 2.f, 0.f);
		textObj.setPosition(500.f / 4 * 0.5f, 500.f / 4 * 0.8f);
		textObj.setFillColor(sf::Color(255, 200, 150));
		textObj.setOutlineThickness(0.f);
	}

	// test FPS display
	sf::Text fpsTextObj("0.00 fps", gameResourceManager.getFontRef("freecam_font"), 8);
	sf::Clock fpsClock;
	std::stringstream fpsStrStream;
	{
		fpsTextObj.setPosition(5.f, 5.f);
		fpsTextObj.setFillColor(sf::Color(255, 200, 150));
		fpsTextObj.setOutlineThickness(0.f);
		fpsClock.restart();
	}

	// test some transform stuff
	sf::Transform tf = sf::Transform::Identity;
	{
		const float* m = tf.getMatrix();
	}

	// test tile system stuff
	//Tiles tiles;
	Map map1;
	Map::loadMap1(map1);

	// test body system stuff, note: body system will HAVE to be constructed after the tiles.
	BodySystem testBodySystem(map1);
	BulletSystem bulletSystem(testBodySystem);

	// update loop
	Tank player1(50, 125, 10, Tank::Type::Red);
	Tank player2(430, 125, 10, Tank::Type::Blue);
	testBodySystem.addBody(player1);
	testBodySystem.addBody(player2);

	bool player1FireInput = sf::Keyboard::isKeyPressed(sf::Keyboard::F);
	bool player2FireInput = sf::Keyboard::isKeyPressed(sf::Keyboard::RControl);

	while (window.isOpen()) {
		// EVENTS & PROCESS PAUSING
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		// UPDATE LOGIC
		{
			// display fps
			float dt = fpsClock.getElapsedTime().asSeconds();
			float fps = 1 / dt;
			fpsClock.restart();
			fpsStrStream.str("");
			fpsStrStream << std::fixed << std::setprecision(0) << fps;
			fpsTextObj.setString(fpsStrStream.str());
			// update tank
			updateTanks(player1, player2, dt);

			//pdate kinematics
			testBodySystem.update(dt);	
			// update bullets
			bulletSystem.update(dt);
		}
		// shooting test
		{
			bool player1FireInputCurr = sf::Keyboard::isKeyPressed(sf::Keyboard::F);
			if (player1FireInputCurr && player1FireInputCurr != player1FireInput)
				player1.shoot(bulletSystem);
			player1FireInput = player1FireInputCurr;

			bool player2FireInputCurr = sf::Keyboard::isKeyPressed(sf::Keyboard::RControl);
			if (player2FireInputCurr && player2FireInputCurr != player2FireInput)
				player2.shoot(bulletSystem);
			player2FireInput = player2FireInputCurr;
		}
		// RENDERING
		{
			
			window.clear(sf::Color::White);
			map1.printMap(window);
			// draw background layer?
			//window.draw(tiles);
			// draw object layer
			window.draw(player1); // add draw statment for the other tank
			window.draw(player2);
			window.draw(bulletSystem);
			// draw debug layer
			//testBodySystem.debug_drawBodies(window);
			testBodySystem.debug_drawCollisions(window);
			// draw ui layer
			window.draw(fpsTextObj);
			// push pixel buffer to be drawn
			window.display(); // this should probably be called last
		}
	}
}
#endif
void updateTanks(Tank& tank1, Tank& tank2, float dt) {
	using sf::Keyboard;
	/* PLAYER 1 */
	tank1.setForward(Keyboard::isKeyPressed(Keyboard::W)); // note: the boolean gets casted to a float as 0f or 1f
	tank1.setBack(Keyboard::isKeyPressed(Keyboard::S));
	tank1.setLeft(Keyboard::isKeyPressed(Keyboard::A));
	tank1.setRight(Keyboard::isKeyPressed(Keyboard::D));
	tank1.update(dt);
	/* PLAYER 2*/
	tank2.setForward(Keyboard::isKeyPressed(Keyboard::Up)); // note: the boolean gets casted to a float as 0f or 1f
	tank2.setBack(Keyboard::isKeyPressed(Keyboard::Down));
	tank2.setLeft(Keyboard::isKeyPressed(Keyboard::Left));
	tank2.setRight(Keyboard::isKeyPressed(Keyboard::Right));
	tank2.update(dt);
}