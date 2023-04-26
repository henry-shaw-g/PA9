/*
	file: GameScene.h
	desc: 
		- class for the main tank battle game scene
		- contains the round state
		- contains the high level drawing behaviour
*/
#pragma once

#include "SFML/Graphics.hpp"
#include "../kinematics/BodySystem.h"

#include "../Scene.h"
#include "../Tank.h"

struct Player {
public:
	Tank* tank; // todo: consider smart pointers here
	int score;
};

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
	Player player1;
	Player player2;
};