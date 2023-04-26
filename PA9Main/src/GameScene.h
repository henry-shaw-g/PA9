/*
	file: GameScene.h
	desc: 
		- class for the main tank battle game scene
		- contains the round state
		- contains the high level drawing behaviour
*/
#pragma once

#include "SFML/Graphics.hpp"
#include "kinematics/BodySystem.h"

#include "Scene.h"
#include "Tank.h"

class GameScene : public Scene {
public:
	GameScene();

	// desc: setup stuff when main loop is ready
	void init() override;

	// desc: update the state of the round (movement, etc)
	void update(float dt) override;

	// desc: render the round
	void draw(sf::RenderTarget& renderTarget) override;

private:
	Tank p1Tank;
	int p1Score;

	Tank p2Tank;
	int p2Score;
};