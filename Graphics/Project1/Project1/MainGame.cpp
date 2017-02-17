#include "MainGame.h"
#include <iostream>

MainGame::MainGame() {

	_screenWidth = 1024;
	_screenHeight = 768;
	_window = nullptr;
	_gameState = GameState::PLAY;
}

MainGame::~MainGame() {


}

void MainGame::run() {

	initSystems();

	gameLoop();

}

void MainGame::gameLoop() {

	while (_gameState != GameState::EXIT) {

		processInput();

	}
}

void MainGame::processInput() {

	SDL_Event evnt;

	while (SDL_PollEvent(&evnt)) {
		// returns 1 if there is a pending event, else false

		switch (evnt.type) {

		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			std::cout << evnt.motion.x << " " << evnt.motion.y << std::endl;
			break;

		}
	}

}

void MainGame::initSystems() {
	//brings sdl into code
	SDL_Init(SDL_INIT_EVERYTHING);

	_window = SDL_CreateWindow("Game Engine",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		_screenWidth, _screenHeight,
		SDL_WINDOW_OPENGL);

}
