#pragma once

#include <Bengine\Window.h>
#include <BEngine\GLSLProgram.h>
#include <Bengine\Camera2D.h>
#include <Bengine\InputManager.h>
#include <Bengine\SpriteBatch.h>


#include "Player.h"
#include "Gun.h"
#include "Level.h"
#include "Bullet.h"

class Zombie;

enum class GameState {

	PLAY,
	EXIT

};

class MainGame
{
public:
	MainGame();
	~MainGame();

	/// Runs the game
	void run();

private:
	/// Initializes the core systems
	void initSystems();

	void initLevel();

	/// Initializes the shaders
	void initShaders();

	/// Main game loop for the program
	void gameLoop();

	void updateAgents(float deltaTime);

	void updateBullets(float deltaTime);
	/// Handles input processing
	void processInput();
	/// Renders the game
	void drawGame();


	void checkVictory();

private:
	/// Member Variables
	Bengine::Window _window; ///< The game window
	Bengine::GLSLProgram _textureProgram; ///< The shader program
	Bengine::InputManager _inputManager; ///< Handles input
	Bengine::Camera2D _camera; ///< Main Camera
	Bengine::SpriteBatch _agentSpriteBatch; ///< Main Camera

	std::vector<Level*> _levels;//level storage

	int _screenWidth, screenHeight;

	GameState _gameState;

	float _fps;

	int _numHumansKilled;

	int _numZombiesKilled;

	int _numHumansConverted;

	int _currentLevel;

	Player* _player;
	std::vector<Human*> _humans;
	std::vector<Zombie*> _zombies;
	std::vector<Bullet> _bullets;
};

