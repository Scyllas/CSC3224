#include "MainGame.h"
#include <Bengine/Errors.h>

#include <iostream>
#include <string>

MainGame::MainGame() :
	_screenWidth(1024),
	_screenHeight(768),
	_time(0.f),
	_gameState(GameState::PLAY),
	_maxFPS(60.f)
{
}

MainGame::~MainGame() {


}

void MainGame::run() {

	initSystems();
	_sprites.push_back(new Bengine::Sprite());
	_sprites.back()->init(-1.f, -1.f, 1.f, 1.f, "Textures/jimmyJump_pack/PNG/CharacterRight_Standing.png");

	_sprites.push_back(new Bengine::Sprite());
	_sprites.back()->init(0.f, -1.f, 1.f, 1.f, "Textures/jimmyJump_pack/PNG/CharacterRight_Standing.png");

	_sprites.push_back(new Bengine::Sprite());
	_sprites.back()->init(-1.f, 0.f, 1.f, 1.f, "Textures/jimmyJump_pack/PNG/CharacterRight_Standing.png");

	gameLoop();

}

void MainGame::gameLoop() {

	while (_gameState != GameState::EXIT) {

		float startTicks = SDL_GetTicks();

		processInput();
		_time += 0.01f;
		drawGame();
		calculateFPS();


		//print every 10 frames
		static int frameCount = 0;
		frameCount++;
		if (frameCount == 10) {
			std::cout << _fps << std::endl;
			frameCount = 0;
		}

		//limit fps
		float frameTicks = SDL_GetTicks() - startTicks;
		if (1000.f / _maxFPS > frameTicks) {
			SDL_Delay((1000.f / _maxFPS) - frameTicks);
		}
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
			//	std::cout << evnt.motion.x << " " << evnt.motion.y << std::endl;
			break;

		}
	}

}

void MainGame::initSystems() {

	Bengine::init();

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	_window.create("Game Engine", _screenWidth, _screenHeight, 0);

	initShaders();

}

void MainGame::initShaders() {

	_colourProgram.compileShaders("Shaders/colorShading.vert", "Shaders/colorShading.frag");
	_colourProgram.addAttribute("vertexPosition");
	_colourProgram.addAttribute("vertexColor");
	_colourProgram.addAttribute("vertexUV");
	_colourProgram.linkShaders();
}


void MainGame::drawGame() {

	glClearDepth(1.0);
	//clear both the colour buffer and depth buffer
	//could be done in two functions
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_colourProgram.use();
	glActiveTexture(GL_TEXTURE0);

	GLint textureLocation = _colourProgram.getUniformLocation("mySampler");
	glUniform1i(textureLocation, 0);

	GLuint timeLocation = _colourProgram.getUniformLocation("time");
	glUniform1f(timeLocation, _time);

	for (int i = 0; i < _sprites.size(); i++) {
		_sprites[i]->draw();
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	_colourProgram.unuse();

	_window.swapBuffer();
}

void MainGame::calculateFPS() {

	static const int NUM_SAMPLES = 10;
	static float frameTimes[NUM_SAMPLES];
	static int currentFrame = 0;

	static float prevTicks = SDL_GetTicks();

	float currentTicks;
	currentTicks = SDL_GetTicks();

	_frameTime = currentTicks - prevTicks;
	frameTimes[currentFrame % NUM_SAMPLES] = _frameTime;

	prevTicks = currentTicks;

	int count;

	currentFrame++;

	if (currentFrame < NUM_SAMPLES) {
		count = currentFrame;
	}
	else {
		count = NUM_SAMPLES;
	}

	float frameTimeAverage = 0;
	for (int i = 0; i < count; i++) {
		frameTimeAverage += frameTimes[i];
	}
	frameTimeAverage /= count;

	if (frameTimeAverage > 0) {
		_fps = 1000.f / frameTimeAverage;
	}
	else {
		_fps = 60.f;
	}

}


