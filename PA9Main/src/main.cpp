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
#include "Tank.h"
#include "resources/ResourceManager.h"
#include "Map.h"

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

	// test body system stuff, note: body system will HAVE to be constructed after the tiles.
	BodySystem testBodySystem;
	//CircleBody cb1(Vector2f(0, 100), 20); // note: the life times of these guys need to extend beyond the body class
	//CircleBody cb2(Vector2f(300, 100), 20);
	{
		//testBodySystem.addBody(cb1);
		//testBodySystem.addBody(cb2);
		//cb1.setVelocity(Vector2f(0, 0)); // 5 unit pixels / sec idk
		//cb2.setVelocity(Vector2f(0, 0));
	}

	// update loop

	Tank player1(50, 125, 10, 0);
	Tank player2(430, 125, 10, 1);
	Map map1;
	testBodySystem.addBody(player1);
	testBodySystem.addBody(player2);

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
			testBodySystem.moveObjects(player1, player2, dt); // change this to a body systems or independant function

			// update kinematics
			testBodySystem.update(dt);	
		}
		// shooting test
		{
			float xDir = 0.0, yDir = 0.0;
			Body shot(player1.getPosition());
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
			{
				player1.shoot(xDir, yDir);
				shot.move(xDir, yDir);
			}
			


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
			// draw debug layer
			testBodySystem.debug_drawBodies(window);
			testBodySystem.debug_drawCollisions(window);
			// draw ui layer
			window.draw(fpsTextObj);
			// push pixel buffer to be drawn
			window.display(); // this should probably be called last
		}
	}
}