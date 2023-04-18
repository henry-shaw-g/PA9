
#include <string>
#include <sstream>
#include <iomanip>

#include "SFML/Window.hpp"
#include "SFML/System.hpp"

#include "resources/ResourceManager.h"
#include "TestKinematics.h"

int main(void) {
	//// setup resources
	//ResourceManager::load();
	//ResourceManager& gameResourceManager = ResourceManager::service();

	//// setup sf window
	//sf::RenderWindow window(sf::VideoMode(500, 500), "WINDOW");
	//sf::Event event;
	//{
	//	window.setFramerateLimit(120);
	//}
	//
	//// testing texture manager
	//sf::Sprite sprite;
	//{
	//	sprite.setTexture(gameResourceManager.getTextureRef("smiley_face_0"));
	//	sprite.setOrigin(sf::Vector2f(32.0f, 32.0f));
	//	sprite.setPosition(sf::Vector2f(500.f / 4 / 2, 500.f / 4 / 2));
	//}
	//
	//// testing font manager
	//sf::Text textObj("what", gameResourceManager.getFontRef("freecam_font"), 10);
	//{
	//	textObj.setOrigin(textObj.getGlobalBounds().width / 2.f, 0.f);
	//	textObj.setPosition(500.f / 4 * 0.5f, 500.f / 4 * 0.8f);
	//	textObj.setFillColor(sf::Color(255, 200, 150));
	//	textObj.setOutlineThickness(0.f);
	//}

	//// test FPS display
	//sf::Text fpsTextObj("0.00 fps", gameResourceManager.getFontRef("freecam_font"), 8);
	//sf::Clock fpsClock;
	//std::stringstream fpsStrStream;
	//{
	//	fpsTextObj.setPosition(5.f, 5.f);
	//	fpsTextObj.setFillColor(sf::Color(255, 200, 150));
	//	fpsTextObj.setOutlineThickness(0.f);
	//	fpsClock.restart();
	//}

	//// update loop
	//while (window.isOpen()) {
	//	while (window.pollEvent(event)) {
	//		if (event.type == sf::Event::Closed) {
	//			window.close();
	//		}
	//	}
	//	window.clear();

	//	// update window size
	//	sf::Vector2u size = window.getSize();
	//	sf::FloatRect view(0.f, 0.f, size.x / 4, size.y / 4);
	//	window.setView(sf::View(view));

	//	// display fps
	//	float dt = fpsClock.getElapsedTime().asSeconds();
	//	float fps = 1 / dt;
	//	fpsClock.restart();
	//	fpsStrStream.str("");
	//	fpsStrStream << std::fixed << std::setprecision(0) << fps;
	//	fpsTextObj.setString(fpsStrStream.str());
	//	
	//	// ok
	//	window.draw(sprite);
	//	window.draw(textObj);
	//	window.draw(fpsTextObj);
	//	window.display();
	//}

	// test kinematics
	sf::RenderWindow window(sf::VideoMode(500, 500), "WINDOW", 
		sf::Style::Default & (~sf::Style::Resize));
	sf::Event event;
	sf::Clock clock;
	{
		window.setFramerateLimit(120);
	}

	sf::RenderTexture windowTexture;
	{
		windowTexture.create(100, 100);
		window.setView(windowTexture.getView());
	}

	TestKinematics scene;
	{
		scene.init();
	}

	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		
		float dt = clock.getElapsedTime().asSeconds();
		clock.restart();

		window.clear();
		windowTexture.clear();

		scene.update(dt);
		scene.draw(windowTexture);

		windowTexture.display();
		sf::Sprite sprite(windowTexture.getTexture());
		window.draw(sprite);
		window.display();
	}

}