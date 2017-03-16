#include "MainGame.h"
#include <SDL/SDL.h>
#include <fstream>
#include <iostream>
#include <Bengine\Bengine.h>
#include <Bengine/timing.h>
#include "Zombie.h"
#include <random>
#include <ctime>
#include <algorithm>

const float HUMAN_SPEED = 1.f;
const float ZOMBIE_SPEED = 1.3f;
const float PLAYER_SPEED = 5.f;

MainGame::MainGame() :
	_screenWidth(1024),
	screenHeight(768),
	_gameState(GameState::PLAY),
	_fps(0),
	_player(nullptr),
	_numZombiesKilled(0),
	_numHumansKilled(0),
	_numHumansConverted(0) {
	// Empty
}

MainGame::~MainGame()
{
	for (int i = 0; i < _levels.size(); i++) {
		delete _levels[i];
	}
	for (int i = 0; i < _humans.size(); i++) {
		delete _humans[i];
	}
	for (int i = 0; i < _zombies.size(); i++) {
		delete _zombies[i];
	}
}

void MainGame::run() {

	initSystems();
	initLevel();

	gameLoop();

}

void MainGame::initSystems() {
	Bengine::init();

	_window.create("ZombieGame", _screenWidth, screenHeight, 0);
	glClearColor(0.7f, 0.7f, 0.7f, 1.f);
	initShaders();

	_agentSpriteBatch.init();

	_camera.init(_screenWidth, screenHeight);


}

void MainGame::initLevel() {

	_levels.push_back(new Level("Levels/level1.txt"));
	_currentLevel = 0;

	_player = new Player();
	_player->init(PLAYER_SPEED, _levels[_currentLevel]->getStartPlayerPos(), &_inputManager, &_camera, &_bullets);

	_humans.push_back(_player);

	static std::mt19937 randomEngine;
	randomEngine.seed(time(nullptr));
	static std::uniform_int_distribution<int> randX(1, _levels[_currentLevel]->getWidth() - 2);
	static std::uniform_int_distribution<int> randY(1, _levels[_currentLevel]->getHeight() - 2);



	for (int i = 0; i < _levels[_currentLevel]->getNumHumans(); i++) {

		_humans.push_back(new Human);
		glm::vec2 pos(randX(randomEngine) * TILE_WIDTH, randY(randomEngine) *TILE_WIDTH);
		_humans.back()->init(HUMAN_SPEED, pos);
	}

	const std::vector<glm::vec2>& zombiePositions = _levels[_currentLevel]->getZombieStartPositions();

	for (int i = 0; i < zombiePositions.size(); i++) {

		_zombies.push_back(new Zombie);
		_zombies.back()->init(ZOMBIE_SPEED, zombiePositions[i]);
	}

	const float BULLET_SPEED = 20.f;
	_player->addGun(new Gun("Magnum", 10, 1, 5.f, 30, BULLET_SPEED));
	_player->addGun(new Gun("Shotgun", 30, 20, 20.f, 4, BULLET_SPEED));
	_player->addGun(new Gun("SMG", 2, 1, 10.f, 20, BULLET_SPEED));
}

void MainGame::initShaders() {
	// Compile our color shader
	_textureProgram.compileShaders("Shaders/textureShading.vert", "Shaders/textureShading.frag");
	_textureProgram.addAttribute("vertexPosition");
	_textureProgram.addAttribute("vertexColor");
	_textureProgram.addAttribute("vertexUV");
	_textureProgram.linkShaders();
}

void MainGame::gameLoop() {


	Bengine::FpsLimiter fpsLimiter;

	const float DESIRED_FPS = 60.f;
	const int MAX_PHYSICS_STEPS = 6;

	fpsLimiter.setMaxFPS(DESIRED_FPS);

	const float CAMERA_SCALE = 0.25f;
	_camera.setScale(CAMERA_SCALE);

	const float MS_PER_SECOND = 1000.f;
	const float DESIRED_FRAMETIME = MS_PER_SECOND / DESIRED_FPS;
	const float MAX_DELTA_TIME = 1.f;
	float prevTicks = SDL_GetTicks();

	while (_gameState == GameState::PLAY) {

		fpsLimiter.begin();

		float newTicks = SDL_GetTicks();
		float frameTime = newTicks - prevTicks;
		prevTicks = newTicks;
		float totalDeltaTime = frameTime / DESIRED_FRAMETIME;

		checkVictory();

		_inputManager.update();

		processInput();

		//timestepped updates
		int i = 0;
		while (totalDeltaTime > 0.f) {

			float deltaTime = std::min(totalDeltaTime, MAX_DELTA_TIME);

			updateAgents(deltaTime);

			updateBullets(deltaTime);

			totalDeltaTime -= deltaTime;

			i++;
		}

		_camera.setPosition(_player->getPosition());

		_camera.update();

		drawGame();

		_fps = fpsLimiter.end();
	}

}

void MainGame::checkVictory() {

	if (_zombies.empty()) {
		std::printf("************ WINNER, YOU KILLED %d ZOMBIES AND MURDERED %d HUMANS, THE ZOMBIES TURNED %d PEOPLE",
			_numZombiesKilled, _numHumansKilled, _numHumansConverted);
		Bengine::fatalError("");
	}
}
void MainGame::updateAgents(float deltaTime) {

	//update humans
	for (int i = 0; i < _humans.size(); i++) {
		_humans[i]->update(_levels[_currentLevel]->getLevelData(), _humans, _zombies, deltaTime);
	}
	//update zombies
	for (int i = 0; i < _zombies.size(); i++) {
		_zombies[i]->update(_levels[_currentLevel]->getLevelData(), _humans, _zombies, deltaTime);
	}

	//update zombie collisions
	for (int i = 0; i < _zombies.size(); i++) {
		//colliding with zombies
		for (int j = i + 1; j < _zombies.size(); j++) {
			_zombies[i]->collideWithAgent(_zombies[j]);
		}
		//with humans
		for (int j = 1; j < _humans.size(); j++) {
			if (_zombies[i]->collideWithAgent(_humans[j])) {
				//create new zombie
				_zombies.push_back(new Zombie);
				_zombies.back()->init(ZOMBIE_SPEED, _humans[j]->getPosition());
				//delete human
				_numHumansConverted++;
				delete _humans[j];
				_humans[j] = _humans.back();
				_humans.pop_back();
			}
		}

		//collide with player
		if (_zombies[i]->collideWithAgent(_player)) {
			Bengine::fatalError("You Lose");
		}

	}
	//update humans collisions
	for (int i = 0; i < _humans.size(); i++) {
		//colliding with humans
		for (int j = i + 1; j < _humans.size(); j++) {
			_humans[i]->collideWithAgent(_humans[j]);
		}
	}

}

void MainGame::updateBullets(float deltaTime) {

	//collision with world
	for (int i = 0; i < _bullets.size();) {
		if (_bullets[i].update(_levels[_currentLevel]->getLevelData(), deltaTime) == true) {
			_bullets[i] = _bullets.back();
			_bullets.pop_back();
		}
		else {
			i++;
		}
	}

	bool wasBulletRemoved = false;
	//collision with agents
	for (int i = 0; i < _bullets.size(); i++) {


		wasBulletRemoved = false;
		for (int j = 0; j < _zombies.size(); ) {
			if (_bullets[i].collideWithAgent(_zombies[j])) {
				if (_zombies[j]->applyDamage(_bullets[i].getDamage())) {
					_numZombiesKilled++;
					delete _zombies[j];
					_zombies[j] = _zombies.back();
					_zombies.pop_back();
				}
				else {
					j++;
				}
				_bullets[i] = _bullets.back();
				_bullets.pop_back();
				wasBulletRemoved = true;
				//bullet found target, new iteration
				break;
			}
			else {
				j++;
			}
		}

		if (wasBulletRemoved == false) {
			//j = 1 avoid self collision
			for (int j = 1; j < _humans.size(); ) {
				if (_bullets[i].collideWithAgent(_humans[j])) {
					if (_humans[j]->applyDamage(_bullets[i].getDamage())) {
						_numHumansKilled++;
						delete _humans[j];
						_humans[j] = _humans.back();
						_humans.pop_back();
					}
					else {
						j++;
					}
					_bullets[i] = _bullets.back();
					_bullets.pop_back();
					wasBulletRemoved = true;
					//bullet found target, new iteration
					break;
				}
				else {
					j++;

				}
			}
		}
	}
}

void MainGame::processInput() {
	SDL_Event evnt;

	//Will keep looping until there are no more events to process
	while (SDL_PollEvent(&evnt)) {
		switch (evnt.type) {
		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			_inputManager.setMouseCoords(evnt.motion.x, evnt.motion.y);
			break;
		case SDL_KEYDOWN:
			_inputManager.pressKey(evnt.key.keysym.sym);
			break;
		case SDL_KEYUP:
			_inputManager.releaseKey(evnt.key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
			_inputManager.pressKey(evnt.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			_inputManager.releaseKey(evnt.button.button);
			break;
		}

	}

}

void MainGame::drawGame() {
	// Set the base depth to 1.0
	glClearDepth(1.0);
	// Clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_textureProgram.use();

	//Draw code goes here
	glActiveTexture(GL_TEXTURE0);

	GLint textureUniform = _textureProgram.getUniformLocation("mySampler");
	glUniform1i(textureUniform, 0);

	//grab cam matrix
	glm::mat4 projectionMatrix = _camera.getCameraMatrix();

	GLint pUniform = _textureProgram.getUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

	//draw level
	_levels[_currentLevel]->draw();

	_agentSpriteBatch.begin();

	glm::vec2 agentPos;
	glm::vec2 agentDims(AGENT_RADIUS * 2.f);

	//draw humans
	for (int i = 0; i < _humans.size(); i++) {
		if (_camera.isBoxInView(_humans[i]->getPosition(), agentDims)) {
			_humans[i]->draw(_agentSpriteBatch);
		}
	}
	//draw zombies
	for (int i = 0; i < _zombies.size(); i++) {
		if (_camera.isBoxInView(_zombies[i]->getPosition(), agentDims)) {
			_zombies[i]->draw(_agentSpriteBatch);
		}
	}
	//draw bullets
	for (int i = 0; i < _bullets.size(); i++) {
		_bullets[i].draw(_agentSpriteBatch);
	}

	_agentSpriteBatch.end();
	_agentSpriteBatch.renderBatch();

	_textureProgram.unuse();


	//Swap our buffer and draw everything to the screen!
	_window.swapBuffer();
}