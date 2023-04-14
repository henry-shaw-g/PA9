#include <SFML/Window.hpp>

#include "resources/TextureManager.h"

int main(void) {
	// setup resources
	TextureManager::init();
	TextureManager& gameTextureManager = TextureManager::service();

	// setup sf window
	sf::RenderWindow window(sf::VideoMode(500, 500), "WINDOW");
	sf::Event event;
	
	
	// testing texture manager
	sf::Sprite sprite;
	sprite.setTexture(gameTextureManager.getTextureRef("smiley_face_0"));
	sprite.setOrigin(sf::Vector2f(32.0f, 32.0f));
	sprite.setPosition(sf::Vector2f(500.f / 4 / 2, 500.f / 4 / 2));

	// update loop
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		sf::Vector2u size = window.getSize();
		sf::FloatRect view(0, 0, size.x / 4, size.y / 4);
		window.setView(sf::View(view));

		window.draw(sprite);
		window.display();
	}
}