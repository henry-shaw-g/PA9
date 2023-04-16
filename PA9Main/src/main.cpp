#include <SFML/Window.hpp>

#include "resources/ResourceManager.h"

int main(void) {
	// setup resources
	ResourceManager::load();
	ResourceManager& gameResourceManager = ResourceManager::service();

	// setup sf window
	sf::RenderWindow window(sf::VideoMode(500, 500), "WINDOW");
	sf::Event event;
	
	
	// testing texture manager
	sf::Sprite sprite;
	{
		sprite.setTexture(gameResourceManager.getTextureRef("smiley_face_0"));
		sprite.setOrigin(sf::Vector2f(32.0f, 32.0f));
		sprite.setPosition(sf::Vector2f(500.f / 4 / 2, 500.f / 4 / 2));
	}
	
	// testing font manager
	sf::Text textObj("what", gameResourceManager.getFontRef("freecam_font"), 10);
	textObj.setOrigin(textObj.getGlobalBounds().width / 2.f, 0.f);
	textObj.setPosition(500.f / 4 * 0.5f, 500.f / 4 * 0.8f);
	textObj.setFillColor(sf::Color(255, 200, 150));
	textObj.setOutlineThickness(0.f);

	// update loop
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		window.clear();

		sf::Vector2u size = window.getSize();
		sf::FloatRect view(0.f, 0.f, size.x / 4, size.y / 4);
		window.setView(sf::View(view));

		window.draw(sprite);
		window.draw(textObj);
		window.display();
	}
}