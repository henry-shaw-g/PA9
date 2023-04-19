#include "Tank.h"

void Tank::moveObject(sf::RenderWindow& window) {

	while (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		window.clear();
		move(.1 * cos(radians), .1 * sin(radians));
		texture.move(.1 * cos(radians), .1 * sin(radians));
		window.draw(*this);
		window.draw(texture);
		window.display();
	}

	while (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		window.clear();
		move(-.1 * cos(radians), -.1 * sin(radians));
		texture.move(-.1 * cos(radians), -.1 * sin(radians));
		window.draw(*this);
		window.draw(texture);
		window.display();
	}

	while (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		window.clear();
		rotate(maxAngV);
		setRadians();
		texture.rotate(maxAngV);
		window.draw(*this);
		window.draw(texture);
		window.display();
	}

	while (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		window.clear();
		rotate(-maxAngV);
		setRadians();
		texture.rotate(-maxAngV);
		window.draw(*this);
		window.draw(texture);
		window.display();
	}
}