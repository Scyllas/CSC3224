#pragma once

#include <Bengine\Window.h>
#include <BEngine\GLSLProgram.h>
#include <Bengine\Camera2D.h>
#include <Bengine\InputManager.h>
#include <Bengine\SpriteBatch.h>
#include <Bengine\SpriteFont.h>
#include <Bengine\Bengine.h>
#include <Bengine\timing.h>
#include <Bengine\BengineErrors.h>
#include <Bengine\AudioEngine.h>
#include <Bengine\ParticleBatch2D.h>
#include <Bengine\ParticleEngine2D.h>
#include <Bengine\ResourceManager.h>

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
	Bengine::Window m_window; ///< The game window
	Bengine::GLSLProgram m_textureProgram; ///< The shader program
	Bengine::InputManager m_inputManager; ///< Handles input
	Bengine::Camera2D m_camera; ///< Main Camera
	Bengine::Camera2D m_hudCamera; ///< Main Camera
	Bengine::SpriteBatch m_agentSpriteBatch; ///< Main Camera
	Bengine::SpriteBatch m_hudSpriteBatch;

	Bengine::ParticleEngine2D m_particleEngine;
	Bengine::ParticleBatch2D* m_bloodParticleBatch;

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

	Bengine::SpriteFont* m_spriteFont;
	Bengine::AudioEngine m_audioEngine;


	GameState m_gameState = GameState::PLAY;
};

