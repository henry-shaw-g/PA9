/*
	file: Game.cpp
	note: we kind of went back to caveman C in this part (it was pretty late :C)
*/

#include "Game.h"

Game::Game()
{
	map = std::make_unique<Map>();
	bodySystem = std::make_unique<BodySystem>(*map);
	bulletSystem = std::make_unique<BulletSystem>(*bodySystem);
}

void Game::init() {
	Map::loadMap1(*map);

	initPlayer(player1, Tank::Type::Red, Vector2f(50, 125));
	player1.scoreText.setFillColor(sf::Color::Red);
	player1.scoreText.setCharacterSize(10);
	player1.scoreText.setFont(ResourceManager::service().getFontRef("freecam_font"));
	player1.scoreText.setString("Score: 0");
	player1.scoreText.setOrigin(player1.scoreText.getLocalBounds().width / 2, 0);
	player1.scoreText.setPosition(70, 10);

	initPlayer(player2, Tank::Type::Blue, Vector2f(430, 125));
	player2.scoreText.setFillColor(sf::Color::Blue);
	player2.scoreText.setFont(ResourceManager::service().getFontRef("freecam_font"));
	player2.scoreText.setString("Score: 0");
	player2.scoreText.setCharacterSize(10);
	player2.scoreText.setOrigin(player2.scoreText.getLocalBounds().width / 2, 0);
	player2.scoreText.setPosition(410, 10);

	spawnPlayer(player1, player1.spawnPos);
	spawnPlayer(player2, player2.spawnPos);
}

void Game::update(float dt) 
{
	// update tanks and input
	updateInput();
	if (player1.tank)
		player1.tank->update(dt);
	if (player2.tank)
		player2.tank->update(dt);
	// update motion
	bodySystem->update(dt);
	// update bullets
	bulletSystem->update(dt);

	// process bullet events
	BulletEvent bulletEvent;
	while (bulletSystem->pollEvent(bulletEvent)) {
		if (bulletEvent.type == BulletEvent::HitBody) {
			onBulletHit(bulletEvent);
		}
	}
}

void Game::draw(sf::RenderTarget& renderTarget) 
{
	// draw map
	map->printMap(renderTarget);
	// draw tanks
	renderTarget.draw(*player1.tank);
	renderTarget.draw(*player2.tank);
	// draw bullets
	renderTarget.draw(*bulletSystem);
	// draw UI
	renderTarget.draw(player1.scoreText);
	renderTarget.draw(player2.scoreText);
}

void Game::initPlayer(Player& player, Tank::Type tankType, Vector2f spawnPos) {
	player.score = 0;
	player.tankType = tankType;
	player.tank = nullptr;
	player.shootDown = false;
	player.spawnPos = spawnPos;
}

void Game::spawnPlayer(Player& player, Vector2f pos) {
	player.tank = std::make_unique<Tank>(pos, 10, player.tankType);
	bodySystem->addBody(*player.tank);
}

void Game::updateInput() {
	using sf::Keyboard;
	// PLAYER 1 INPUT
	{
		bool shootDownCurr = sf::Keyboard::isKeyPressed(sf::Keyboard::F);
		if (player1.tank) {
			player1.tank->setForward(Keyboard::isKeyPressed(Keyboard::W)); // note: the boolean gets casted to a float as 0f or 1f
			player1.tank->setBack(Keyboard::isKeyPressed(Keyboard::S));
			player1.tank->setLeft(Keyboard::isKeyPressed(Keyboard::A));
			player1.tank->setRight(Keyboard::isKeyPressed(Keyboard::D));
			// TODO: consider key pressed state object
			if (shootDownCurr && shootDownCurr != player1.shootDown) {
				player1.tank->shoot(*bulletSystem);
			}
		}
		player1.shootDown = shootDownCurr;
	}
	// PLAYER 2 INPUT
	{
		bool shootDownCurr = sf::Keyboard::isKeyPressed(sf::Keyboard::RControl);
		if (player2.tank) {
			player2.tank->setForward(Keyboard::isKeyPressed(Keyboard::Up)); // note: the boolean gets casted to a float as 0f or 1f
			player2.tank->setBack(Keyboard::isKeyPressed(Keyboard::Down));
			player2.tank->setLeft(Keyboard::isKeyPressed(Keyboard::Left));
			player2.tank->setRight(Keyboard::isKeyPressed(Keyboard::Right));
			if (shootDownCurr && shootDownCurr != player2.shootDown) {
				player2.tank->shoot(*bulletSystem);
			}
		}
		player2.shootDown = shootDownCurr;
	}
}

void Game::onBulletHit(const BulletEvent& bulletEvent) {
	if (bulletEvent.type != BulletEvent::HitBody) { // jic
		return;
	}
	if (player1.tank && bulletEvent.hitBody.bodyId == player1.tank->getId()) {
		// kill player 1 tank
		onPlayerKilled(player1, player2);
	}
	else if (player2.tank && bulletEvent.hitBody.bodyId == player2.tank->getId()) {
		// kill player 2 tank
		onPlayerKilled(player2, player1);
	}
}

void Game::onPlayerKilled(Player& died, Player& alive)
{
	++alive.score;
	alive.scoreText.setString("Score: " + std::to_string(alive.score));
	if (died.tank) {
		bodySystem->removeBody(*died.tank);
		died.tank.reset();
	}
	spawnPlayer(died, died.spawnPos);
}

