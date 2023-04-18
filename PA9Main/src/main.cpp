#define _USE_MATH_DEFINES
#include <math.h>

#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>

#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "resources/Tank.h"

#include "resources/ResourceManager.h"

int main(void) {
	// setup resources
	ResourceManager::load();
	ResourceManager& gameResourceManager = ResourceManager::service();

	// setup sf window
	sf::RenderWindow window(sf::VideoMode(500, 500), "WINDOW");
	sf::Event event;
	{
		window.setFramerateLimit(120);
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

	// update loop

	Tank newPlayer(50, 100, 2.5);
	window.draw(newPlayer);
	window.display();

	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		window.clear();

		// update window size
		sf::Vector2u size = window.getSize();
		sf::FloatRect view(0.f, 0.f, size.x / 4, size.y / 4);
		window.setView(sf::View(view));

		// display fps
		float dt = fpsClock.getElapsedTime().asSeconds();
		float fps = 1 / dt;
		fpsClock.restart();
		fpsStrStream.str("");
		fpsStrStream << std::fixed << std::setprecision(0) << fps;
		fpsTextObj.setString(fpsStrStream.str());
		
		window.draw(fpsTextObj);

		newPlayer.moveObject(window);
		window.draw(newPlayer);
		

		/*while (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			window.clear();
			window.draw(newPlayer);
			window.display();
		}*/

		window.display(); // this should probably be called last
	}
}