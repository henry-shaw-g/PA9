#include "Tank.h"

void Tank::moveObject(sf::RenderWindow& window) {
	// note: do not call window clear or window display in individual rendering steps, those should only be called at the begining / end of the frame
	// also we only need to check the key state one time each frame so these should be if statements rather than while loops

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		move(.1 * cos(radians), .1 * sin(radians));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		move(-.1 * cos(radians), -.1 * sin(radians));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		rotate(maxAngV);
		setRadians();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		rotate(-maxAngV);
		setRadians();
	}
}