#include "Tank.h"

Tank::Tank(float initX, float initY, float radius) : CircleBody(Vec2f(initX, initY), radius) {
	maxV = 0.5;
	maxAngV = 1; // this can stay here
	radians = 0;

	// setup chassis sprite
	const sf::Texture& tankTextureRef = ResourceManager::service()
		.getTextureRef("tank_blue");
	chassisSprite.setTexture(tankTextureRef);
	chassisSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
	// this will all be relative to the tank position / rotation after we do some stuff
	chassisSprite.setOrigin(radius, radius);
	chassisSprite.setRotation(0.f);

	// setup turret sprite
	turretSprite.setTexture(tankTextureRef);
	turretSprite.setTextureRect(sf::IntRect(32, 0, 64, 32));
	turretSprite.setOrigin(radius, radius);
	turretSprite.setRotation(0.f);
}


void Tank::draw(sf::RenderTarget & renderTarget, sf::RenderStates _) const {
	// i dont think the circle drawer gets called anymore
	sf::Transform tankTransform = getTransform();
	
	// use the transform to draw component sprites relatively:
	renderTarget.draw(chassisSprite, tankTransform);
	renderTarget.draw(turretSprite, tankTransform);
}

void Tank::moveObject() {
	// note: do not call window clear or window display in individual rendering steps, those should only be called at the begining / end of the frame
	// also we only need to check the key state one time each frame so these should be if statements rather than while loops

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		move(getFrontDir() * -.5f);
		//move(.1 * cos(radians), .1 * sin(radians));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		move(getFrontDir() * .5f);
		//move(-.1 * cos(radians), -.1 * sin(radians));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		rotate(maxAngV);
		//setRadians();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		rotate(-maxAngV);
		//setRadians();
	}
}

Vec2f Tank::getFrontDir() const {
	const float* matrix = getTransform().getMatrix();
	// this is like the basis x vector for the rotation of the tank (forward)
	// its a 4x4 matrix for some reason
	return Vec2f(matrix[4], matrix[5]);
}

Vec2f Tank::getRightDir() const {
	const float* matrix = getTransform().getMatrix();
	// this is the basis y vector for the rotation of the tank (right?)
	return Vec2f(matrix[0], matrix[1]);
}