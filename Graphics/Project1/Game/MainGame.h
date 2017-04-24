#pragma once

#include <Engine\Window.h>
#include <BEngine\GLSLProgram.h>
#include <Engine\Camera2D.h>
#include <Engine\InputManager.h>
#include <Engine\SpriteBatch.h>
#include <Engine\SpriteFont.h>
#include <Engine\Engine.h>
#include <Engine\timing.h>
#include <Engine\EngineErrors.h>
#include <Engine\AudioEngine.h>
#include <Engine\ParticleBatch2D.h>
#include <Engine\ParticleEngine2D.h>
#include <Engine\ResourceManager.h>

#include <SDL\SDL.h>
#include <fstream>
#include <iostream>

#include <random>
#include <ctime>
#include <algorithm>

#include "Zombie.h"
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

	void drawHud();

	void addBlood(const glm::vec2& position, int numParticles);

	void checkVictory();

	/// Member Variables
	Engine::Window m_window; ///< The game window
	Engine::GLSLProgram m_textureProgram; ///< The shader program
	Engine::InputManager m_inputManager; ///< Handles input
	Engine::Camera2D m_camera; ///< Main Camera
	Engine::Camera2D m_hudCamera; ///< Main Camera
	Engine::SpriteBatch m_agentSpriteBatch; ///< Main Camera
	Engine::SpriteBatch m_hudSpriteBatch;

	Engine::ParticleEngine2D m_particleEngine;
	Engine::ParticleBatch2D* m_bloodParticleBatch;

	std::vector<Level*> m_levels;//level storage

	int m_screenWidth = 1024;
	int	m_screenHeight = 768;

	float m_fps = 0;

	int m_currentLevel;


	Player* m_player = nullptr;
	std::vector<Human*> m_humans;
	std::vector<Zombie*> m_zombies;
	std::vector<Bullet> m_bullets;

	int m_numHumansKilled = 0;
	int m_numZombiesKilled = 0;
	int m_numHumansConverted = 0;

	Engine::SpriteFont* m_spriteFont;
	Engine::AudioEngine m_audioEngine;


	GameState m_gameState = GameState::PLAY;
};

