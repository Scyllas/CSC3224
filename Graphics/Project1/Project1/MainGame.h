#pragma once

#include <SDL/SDL.h>
#include <GL/glew.h>

#include <Bengine\Bengine.h>
#include <Bengine/GLSLProgram.h>
#include <Bengine/Sprite.h>
#include <Bengine/GLTexture.h>
#include <vector>
#include <Bengine/Window.h>
#include <Bengine/InputManager.h>
#include <Bengine/Timing.h>
#include <Bengine\SpriteFont.h>

#include "Bullets.h"

#include <Bengine\Camera2D.h>

#include <Bengine\SpriteBatch.h>
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

	Bengine::Window m_window;
	int m_screenWidth = 1024;
	int m_screenHeight = 768;
	GameState m_gameState = GameState::PLAY;

	Bengine::GLSLProgram m_colourProgram;
	Bengine::Camera2D m_camera;
	Bengine::Camera2D m_hudCamera;

	Bengine::SpriteBatch m_spriteBatch;
	Bengine::SpriteBatch m_hudSpriteBatch;

	Bengine::InputManager m_inputManager;

	Bengine::FpsLimiter m_fpsLimiter;

	std::vector<Bullets> m_bullets;

	float m_time = 0.f;
	float m_fps;
	float m_maxFPS = 60.f;

	Bengine::SpriteFont* m_spriteFont;
};