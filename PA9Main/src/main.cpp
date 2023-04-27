#define _USE_MATH_DEFINES
#include <math.h>

#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>

#include "SFML/Window.hpp"
#include "SFML/System.hpp"

#include "resources/ResourceManager.h"
#include "Game.h"
#include "GameConfig.h"
#include "math/Misc.h"

#include "tests/TestMain.h"

#if 0
int main() {
	Tests::run();
}
#else
int main(void) {
	// setup resources
	ResourceManager::load();
	ResourceManager& gameResourceManager = ResourceManager::service();

	// setup sf window (non-fullscreen, non-resizable)
	sf::VideoMode videoMode(1440, 810);
	sf::RenderWindow window(videoMode, "Tanks", sf::Style::Default & (~sf::Style::Resize));;
	sf::Event event;
	{
		window.setFramerateLimit(120);
		sf::FloatRect view(0.f, 0.f, 480, 270);
		window.setView(sf::View(view));
	}

	// setup clock
	sf::Clock clock;

	// setup game
	Game gameObject;
	gameObject.init();

	while (window.isOpen()) {
		// EVENTS & PROCESS PAUSING
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		// UPDATES
		float dt = clock.getElapsedTime().asSeconds();
		clock.restart();
		gameObject.update(dt);
		// RENDERING
		window.clear(sf::Color::White);
		gameObject.draw(window);
		window.display();
	}

	return 0;
}
#endif