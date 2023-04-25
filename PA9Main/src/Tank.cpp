#include "Tank.h"

Tank::Tank(float initX, float initY, float radius) : CircleBody(Vector2f(initX, initY), radius) {
	maxV = 50;
	maxAngV = 110; // deg / s?
	radians = 0;
	setPosition(initX, initY);

	// initialize input
	forwardInput = 0;
	backInput = 0;
	leftInput = 0;
	rightInput = 0;

	// setup chassis sprite
	const sf::Texture& tankTextureRef = ResourceManager::service()
		.getTextureRef("tank");
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
	/*renderTarget.draw(chassisSprite, tankTransform);
	renderTarget.draw(turretSprite, tankTransform);*/
	renderTarget.draw(chassisSprite, tankTransform);
}

void Tank::update(float dt) {
	// note: do not call window clear or window display in individual rendering steps, those should only be called at the begining / end of the frame
	// also we only need to check the key state one time each frame so these should be if statements rather than while loops

	float move = forwardInput - backInput;
	float turn = rightInput - leftInput;

	setVelocity(-getFrontDir() * move * maxV);
	rotate(turn * maxAngV * dt);
}

Vector2f Tank::getFrontDir() const {
	const float* matrix = getTransform().getMatrix();
	// this is like the basis x vector for the rotation of the tank (forward)
	// its a 4x4 matrix for some reason
	return Vector2f(matrix[4], matrix[5]);
}

Vector2f Tank::getRightDir() const {
	const float* matrix = getTransform().getMatrix();
	// this is the basis y vector for the rotation of the tank (right?)
	return Vector2f(matrix[0], matrix[1]);
}

void Tank::shoot(float& xVal, float& yVal)
{

	float orientation = 0.0, radians = 0.0;
	orientation = getRotation();
	radians = orientation * (3.14159265359f / 180.0f);
	xVal = std::cos(radians)* .2;
	yVal = std::sin(radians)* .2;
}

// input setters:
void Tank::setForward(float input) { forwardInput = input; }
void Tank::setBack(float input) { backInput = input; }
void Tank::setLeft(float input) { leftInput = input; }
void Tank::setRight(float input) { rightInput = input; }