/*
	file: Game.h
	desc: 
		- class for the main tank battle game scene
		- contains the round state
		- contains the high level drawing behaviour
*/
#pragma once

#include <memory>

#include "SFML/Graphics.hpp"

#include "resources/ResourceManager.h"
#include "kinematics/BodySystem.h"
#include "bullets/BulletSystem.h"

#include "Scene.h"
#include "Tank.h"

struct Player { // note: ran out of time to make this a proper OOP class
public:
	std::unique_ptr<Tank> tank; // todo: consider smart pointers here
	sf::Text scoreText;
	Tank::Type tankType;
	Vector2f spawnPos;
	int score;
	bool shootDown;
};

class Game : public Scene {
public:
	Game();

	// desc: setup stuff when main loop is ready
	void init() override;

	// desc: update the state of the round (movement, etc)
	void update(float dt) override;

	// desc: render the round
	void draw(sf::RenderTarget& renderTarget) override;

private:
	
	// desc: start / restart new round
	void newRound();

	// desc: initialize a player data
	void initPlayer(Player& player, Tank::Type tankType, Vector2f spawnPos);

	// desc: spawn player
	void spawnPlayer(Player& player, Vector2f pos);

	// desc: process input states
	void updateInput();

	// desc: process bullet hit
	void onBulletHit(const BulletEvent& bulletEvent);

	// desc: handle a kill (reset died tank, increase score, etc)
	void onPlayerKilled(Player& died, Player& alive);

	// members:
	Player player1;
	Player player2;
	std::unique_ptr<Map> map;
	std::unique_ptr<BodySystem> bodySystem;
	std::unique_ptr<BulletSystem> bulletSystem;
};