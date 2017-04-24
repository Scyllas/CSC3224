#pragma once

#include <SDL/SDL.h>
#include <GL/glew.h>

#include <Engine\Engine.h>
#include <Engine/GLSLProgram.h>
#include <Engine/Sprite.h>
#include <Engine/GLTexture.h>
#include <vector>
#include <Engine/Window.h>
#include <Engine/InputManager.h>
#include <Engine/Timing.h>
#include <Engine\SpriteFont.h>

#include "Bullets.h"

#include <Engine\Camera2D.h>

#include <Engine\SpriteBatch.h>
enum class GameState { PLAY, EXIT };

class MainGame {

public:

	MainGame();
	~MainGame();

	void run();


private:

	void initSystems();
	void initShaders();
	void gameLoop();
	void processInput();
	void drawGame();
	void drawHudGfx();

	Engine::Window m_window;
	int m_screenWidth = 1024;
	int m_screenHeight = 768;
	GameState m_gameState = GameState::PLAY;

	Engine::GLSLProgram m_colourProgram;
	Engine::Camera2D m_camera;
	Engine::Camera2D m_hudCamera;

	Engine::SpriteBatch m_spriteBatch;
	Engine::SpriteBatch m_hudSpriteBatch;

	Engine::InputManager m_inputManager;

	Engine::FpsLimiter m_fpsLimiter;

	std::vector<Bullets> m_bullets;

	float m_time = 0.f;
	float m_fps;
	float m_maxFPS = 60.f;

	Engine::SpriteFont* m_spriteFont;
};