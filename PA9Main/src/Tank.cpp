#include "Tank.h"

void Tank::moveObject(sf::RenderWindow& window) {

	while (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		//window.clear();
		move(.1 * cos(radians), .1 * sin(radians));
		//window.draw(*this);
		//window.display();
	}

	while (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		//window.clear();
		move(-.1 * cos(radians), -.1 * sin(radians));
		//window.draw(*this);
		//window.display();
	}

	while (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		//window.clear();
		rotate(maxAngV);
		setRadians();
		//window.draw(*this);
		//window.display();
	}

	while (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		//window.clear();
		rotate(-maxAngV);
		setRadians();
		//window.draw(*this);
		//window.display();
	}
}