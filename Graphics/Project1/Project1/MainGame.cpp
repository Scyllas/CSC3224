#include "MainGame.h"

#include <iostream>
#include <string>
#include <algorithm>

MainGame::MainGame()
{
	
}

MainGame::~MainGame() {


}

void MainGame::run() {

	initSystems();

	initLevel();

	gameLoop();

}

void MainGame::gameLoop() {

	const int MAX_PHYSICS_STEPS = 6;
	const float MS_PER_SECOND = 1000.f;
	const float DESIRED_FPS = 60.f;
	const float DESIRED_FRAMETIME = MS_PER_SECOND / DESIRED_FPS;
	const float MAX_DELTA_TIME = 1.f;

	float previousTicks = SDL_GetTicks();

	while (m_gameState != GameState::EXIT) {

		float newTicks = SDL_GetTicks();
		float frameTime = newTicks - previousTicks;
		previousTicks = newTicks;
		float totalDeltaTime = frameTime / DESIRED_FRAMETIME;

		m_fpsLimiter.begin();

		m_inputManager.update();

		processInput();
		m_time += 0.01f;
		int i = 0;
		while (totalDeltaTime > 0.f && i < MAX_PHYSICS_STEPS) {
			float deltaTime = std::min(totalDeltaTime, MAX_DELTA_TIME);
			//things in here to be semi-fixed timestepped

			//before here to be timestepped
			totalDeltaTime -= deltaTime;
			i++;
		}
	//	m_camera.setPosition(m_player->getPo);
		m_camera.update();

		for (int i = 0; i < m_bullets.size();) {

			if (m_bullets[i].update() == true) {

				m_bullets[i] = m_bullets.back();
				m_bullets.pop_back();

			}
			else {
				i++;
			}
		}


		drawGame();



		m_fps = m_fpsLimiter.end();

		//print every 10 frames
		static int frameCount = 0;
		frameCount++;
		if (frameCount == 10000) {
			std::cout << m_fps << std::endl;
			frameCount = 0;
		}

	}
}

void MainGame::processInput() {

	SDL_Event evnt;

	const float CAMERAm_SPEED = 2.f;
	const float SCALEm_SPEED = 0.1f;

	while (SDL_PollEvent(&evnt)) {
		// returns 1 if there is a pending event, else false

		switch (evnt.type) {

		case SDL_QUIT:
			m_gameState = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			m_inputManager.setMouseCoords(evnt.motion.x, evnt.motion.y);
			break;
		case SDL_KEYUP:
			m_inputManager.releaseKey(evnt.key.keysym.sym);
			break;
		case SDL_KEYDOWN:
			m_inputManager.pressKey(evnt.key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
			m_inputManager.pressKey(evnt.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			m_inputManager.releaseKey(evnt.button.button);
			break;


		}
	}

	if (m_inputManager.isKeyDown(SDLK_w)) {
		m_camera.setPosition(m_camera.getPosition() + glm::vec2(0.f, CAMERAm_SPEED));
	}
	if (m_inputManager.isKeyDown(SDLK_s)) {
		m_camera.setPosition(m_camera.getPosition() + glm::vec2(0.f, -CAMERAm_SPEED));
	}
	if (m_inputManager.isKeyDown(SDLK_a)) {
		m_camera.setPosition(m_camera.getPosition() + glm::vec2(-CAMERAm_SPEED, 0.f));
	}
	if (m_inputManager.isKeyDown(SDLK_d)) {
		m_camera.setPosition(m_camera.getPosition() + glm::vec2(CAMERAm_SPEED, 0.f));
	}
	if (m_inputManager.isKeyDown(SDLK_q)) {
		m_camera.setScale(m_camera.getScale() + SCALEm_SPEED);
	}
	if (m_inputManager.isKeyDown(SDLK_e)) {
		m_camera.setScale(m_camera.getScale() - SCALEm_SPEED);
	}

	//change between iskeydown and iskeypressed for hold or press to shoot
	if (m_inputManager.isKeyPressed(SDL_BUTTON_LEFT)) {
		glm::vec2 mouseCoords = m_inputManager.getMouseCoords();
		mouseCoords = m_camera.convertScreenToWorld(mouseCoords);

		glm::vec2 playerPosition(0.f);
		glm::vec2 direction = mouseCoords - playerPosition;
		direction = glm::normalize(direction);

		m_bullets.emplace_back(playerPosition, direction, 5.f, 1000);
	}


}

void MainGame::initSystems() {

	Engine::init();

	m_audioEngine.init();

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	m_window.create("Game Engine", m_screenWidth, m_screenHeight, 0);

	initShaders();

	m_spriteBatch.init();
	m_hudSpriteBatch.init();

	//m_spriteFont = new Engine::SpriteFont("Fonts/ASMAN.ttf", 32);

	m_fpsLimiter.setMaxFPS(m_maxFPS);
	m_camera.init(m_screenWidth, m_screenHeight);
	m_hudCamera.init(m_screenWidth, m_screenHeight);
}

void MainGame::initShaders() {

	m_colourProgram.compileShaders("Shaders/colorShading.vert", "Shaders/colorShading.frag");
	m_colourProgram.addAttribute("vertexPosition");
	m_colourProgram.addAttribute("vertexColor");
	m_colourProgram.addAttribute("vertexUV");
	m_colourProgram.linkShaders();
}


void MainGame::drawGame() {

	glClearDepth(1.0);
	//clear both the colour buffer and depth buffer
	//could be done in two functions
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_colourProgram.use();


	glActiveTexture(GL_TEXTURE0);

	GLint textureLocation = m_colourProgram.getUniformLocation("mySampler");
	glUniform1i(textureLocation, 0);

	GLuint pLocation = m_colourProgram.getUniformLocation("P");
	glm::mat4 cameraMatrix = m_camera.getCameraMatrix();

	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	m_spriteBatch.begin();

	glm::vec4 pos(0.f, 0.f, 50.f, 50.f);
	glm::vec4 uv(0.f, 0.f, 1.f, 1.f);
	static Engine::GLTexture texture = Engine::ResourceManager::getTexture("Textures/jimmyJumpm_pack/PNG/CharacterRightm_Standing.png");
	Engine::ColorRGBA8 color;
	color = Engine::ColorRGBA8(255, 255, 255, 255);


	m_spriteBatch.draw(pos, uv, texture.id, 0.f, color);


	for (int i = 0; i < m_bullets.size(); i++) {
		m_bullets[i].draw(m_spriteBatch);
	}

	m_spriteBatch.end();

	m_spriteBatch.renderBatch();

	//	drawHud();

	glBindTexture(GL_TEXTURE_2D, 0);
	m_colourProgram.unuse();

	m_window.swapBuffer();
}

void MainGame::drawHudGfx() {

	char buffer[256];

	m_hudSpriteBatch.begin();

	sprintf_s(buffer, "Bullets on screen %d", m_bullets.size());
	
	m_spriteFont->draw(
		m_hudSpriteBatch, buffer, glm::vec2(300,300), 
		glm::vec2(4.f), 0.f, Engine::ColorRGBA8(255,255,255,255));

	m_hudSpriteBatch.end();
	m_hudSpriteBatch.renderBatch();


}


