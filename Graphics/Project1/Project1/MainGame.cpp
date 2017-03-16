#include "MainGame.h"
#include <Bengine/Errors.h>

#include <iostream>
#include <string>
#include <algorithm>

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

	gameLoop();

}

void MainGame::gameLoop() {

	const int MAX_PHYSICS_STEPS = 6;
	const float MS_PER_SECOND = 1000.f;
	const float DESIRED_FPS = 60.f;
	const float DESIRED_FRAMETIME = MS_PER_SECOND / DESIRED_FPS;
	const float MAX_DELTA_TIME = 1.f;

	float previousTicks = SDL_GetTicks();

	while (_gameState != GameState::EXIT) {

		float newTicks = SDL_GetTicks();
		float frameTime = newTicks - previousTicks;
		previousTicks = newTicks;
		float totalDeltaTime = frameTime / DESIRED_FRAMETIME;

		_fpsLimiter.begin();

		_inputManager.update();

		processInput();
		_time += 0.01f;
		int i = 0;
		while (totalDeltaTime > 0.f && i < MAX_PHYSICS_STEPS) {
			float deltaTime = std::min(totalDeltaTime, MAX_DELTA_TIME);
			//things in here to be semi-fixed timestepped

			//before here to be timestepped
			totalDeltaTime -= deltaTime;
			i++;
		}
	//	_camera.setPosition(_player->getPo);
		_camera.update();

		for (int i = 0; i < _bullets.size();) {

			if (_bullets[i].update() == true) {

				_bullets[i] = _bullets.back();
				_bullets.pop_back();

			}
			else {
				i++;
			}
		}


		drawGame();



		_fps = _fpsLimiter.end();

		//print every 10 frames
		static int frameCount = 0;
		frameCount++;
		if (frameCount == 10000) {
			std::cout << _fps << std::endl;
			frameCount = 0;
		}

	}
}

void MainGame::processInput() {

	SDL_Event evnt;

	const float CAMERA_SPEED = 2.f;
	const float SCALE_SPEED = 0.1f;

	while (SDL_PollEvent(&evnt)) {
		// returns 1 if there is a pending event, else false

		switch (evnt.type) {

		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			_inputManager.setMouseCoords(evnt.motion.x, evnt.motion.y);
			break;
		case SDL_KEYUP:
			_inputManager.releaseKey(evnt.key.keysym.sym);
			break;
		case SDL_KEYDOWN:
			_inputManager.pressKey(evnt.key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
			_inputManager.pressKey(evnt.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			_inputManager.releaseKey(evnt.button.button);
			break;


		}
	}

	if (_inputManager.isKeyDown(SDLK_w)) {
		_camera.setPosition(_camera.getPosition() + glm::vec2(0.f, CAMERA_SPEED));
	}
	if (_inputManager.isKeyDown(SDLK_s)) {
		_camera.setPosition(_camera.getPosition() + glm::vec2(0.f, -CAMERA_SPEED));
	}
	if (_inputManager.isKeyDown(SDLK_a)) {
		_camera.setPosition(_camera.getPosition() + glm::vec2(-CAMERA_SPEED, 0.f));
	}
	if (_inputManager.isKeyDown(SDLK_d)) {
		_camera.setPosition(_camera.getPosition() + glm::vec2(CAMERA_SPEED, 0.f));
	}
	if (_inputManager.isKeyDown(SDLK_q)) {
		_camera.setScale(_camera.getScale() + SCALE_SPEED);
	}
	if (_inputManager.isKeyDown(SDLK_e)) {
		_camera.setScale(_camera.getScale() - SCALE_SPEED);
	}

	//change between iskeydown and iskeypressed for hold or press to shoot
	if (_inputManager.isKeyPressed(SDL_BUTTON_LEFT)) {
		glm::vec2 mouseCoords = _inputManager.getMouseCoords();
		mouseCoords = _camera.convertScreenToWorld(mouseCoords);

		glm::vec2 playerPosition(0.f);
		glm::vec2 direction = mouseCoords - playerPosition;
		direction = glm::normalize(direction);

		_bullets.emplace_back(playerPosition, direction, 5.f, 1000);
	}


}

void MainGame::initSystems() {

	Bengine::init();

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	_window.create("Game Engine", _screenWidth, _screenHeight, 0);

	initShaders();

	_spriteBatch.init();
	_hudSpriteBatch.init();

	//_spriteFont = new Bengine::SpriteFont("Fonts/ASMAN.ttf", 32);

	_fpsLimiter.setMaxFPS(_maxFPS);
	_camera.init(_screenWidth, _screenHeight);
	_hudCamera.init(_screenWidth, _screenHeight);
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

	GLuint pLocation = _colourProgram.getUniformLocation("P");
	glm::mat4 cameraMatrix = _camera.getCameraMatrix();

	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	_spriteBatch.begin();

	glm::vec4 pos(0.f, 0.f, 50.f, 50.f);
	glm::vec4 uv(0.f, 0.f, 1.f, 1.f);
	static Bengine::GLTexture texture = Bengine::ResourceManager::getTexture("Textures/jimmyJump_pack/PNG/CharacterRight_Standing.png");
	Bengine::ColorRGBA8 color;
	color = Bengine::ColorRGBA8(255, 255, 255, 255);


	_spriteBatch.draw(pos, uv, texture.id, 0.f, color);


	for (int i = 0; i < _bullets.size(); i++) {
		_bullets[i].draw(_spriteBatch);
	}

	_spriteBatch.end();

	_spriteBatch.renderBatch();

	//	drawHud();

	glBindTexture(GL_TEXTURE_2D, 0);
	_colourProgram.unuse();

	_window.swapBuffer();
}

void MainGame::drawHud() {

	char buffer[256];

	_hudSpriteBatch.begin();

	sprintf_s(buffer, "Bullets on screen %d", _bullets.size());
	
	_spriteFont->draw(
		_hudSpriteBatch, buffer, glm::vec2(300,300), 
		glm::vec2(4.f), 0.f, Bengine::ColorRGBA8(255,255,255,255));

	_hudSpriteBatch.end();
	_hudSpriteBatch.renderBatch();


}


