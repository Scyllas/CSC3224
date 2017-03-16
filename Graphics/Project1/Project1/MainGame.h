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
	void drawHud();

	Bengine::Window _window;
	int _screenWidth;
	int _screenHeight;
	GameState _gameState;

	Bengine::GLSLProgram _colourProgram;
	Bengine::Camera2D _camera;
	Bengine::Camera2D _hudCamera;

	Bengine::SpriteBatch _spriteBatch;
	Bengine::SpriteBatch _hudSpriteBatch;

	Bengine::InputManager _inputManager;

	Bengine::FpsLimiter _fpsLimiter;

	std::vector<Bullets> _bullets;

	float _time;
	float _fps;
	float _maxFPS;

	Bengine::SpriteFont* _spriteFont;
};