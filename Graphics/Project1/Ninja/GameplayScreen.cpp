#include "GameplayScreen.h"
#include <iostream>


GameplayScreen::GameplayScreen(Engine::Window * window) :m_window(window) {

	m_screenIndex = SCREEN_INDEX_GAMEPLAY;

}

GameplayScreen::~GameplayScreen()
{
}

int GameplayScreen::getNextScreenIndex() const
{
	return SCREEN_INDEX_NO_SCREEN;
}

int GameplayScreen::getPreviousScreenIndex() const
{
	return SCREEN_INDEX_NO_SCREEN;
}

void GameplayScreen::build()
{
}

void GameplayScreen::destroy()
{
}

void GameplayScreen::onEntry() {

	b2Vec2 gravity(0.0f, -25.f);
	m_world = std::make_unique<b2World>(gravity);

	m_debugRenderer.init();

	//make ground
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.f, -20.f);
	b2Body* groundBody = m_world->CreateBody(&groundBodyDef);
	//make ground fixture
	b2PolygonShape groundBox;
	groundBox.SetAsBox(50.f, 10.f);
	groundBody->CreateFixture(&groundBox, 0.f);

	//load texture
	m_texture = Engine::ResourceManager::getTexture("Assets/bricks_top.png");

	//make multiple boxes
	std::mt19937 randGenerator;
	std::uniform_real_distribution<float> xPos(-10.f, 10.f);
	std::uniform_real_distribution<float> yPos(-10.f, 15.f);
	std::uniform_real_distribution<float> size(0.5f, 2.5f);
	std::uniform_int_distribution<int> color(0, 255);

	const int NUM_BOXES = 10;


	for (int i = 0; i < NUM_BOXES; i++) {

		Engine::ColorRGBA8 randColor = Engine::ColorRGBA8(color(randGenerator), color(randGenerator), color(randGenerator), 255);
		Box newBox;
		newBox.init(m_world.get(), glm::vec2(xPos(randGenerator), yPos(randGenerator)), glm::vec2(size(randGenerator), size(randGenerator)), m_texture, randColor, false, true);
		m_boxes.push_back(newBox);

	}


	m_spriteBatch.init();

	// Compile our texture shader
	m_textureProgram.compileShaders("Shaders/textureShading.vert", "Shaders/textureShading.frag");
	m_textureProgram.addAttribute("vertexPosition");
	m_textureProgram.addAttribute("vertexColor");
	m_textureProgram.addAttribute("vertexUV");
	m_textureProgram.linkShaders();

	// Compile our light shader
	m_lightProgram.compileShaders("Shaders/lightShading.vert", "Shaders/lightShading.frag");
	m_lightProgram.addAttribute("vertexPosition");
	m_lightProgram.addAttribute("vertexColor");
	m_lightProgram.addAttribute("vertexUV");
	m_lightProgram.linkShaders();


	//camera
	m_camera.init(m_window->getScreenWidth(), m_window->getScreenHeight());
	m_camera.setScale(32.f);

	//init player
	m_player.init(m_world.get(), glm::vec2(0.0f, 30.0f), glm::vec2(2.0f), glm::vec2(1.0f, 1.8f), Engine::ColorRGBA8(255, 255, 255, 255));

	initUI();

}


void GameplayScreen::onExit() {

	m_debugRenderer.dispose();

}

void GameplayScreen::update()
{
	m_camera.update();
	checkInput();
	m_player.update(m_game->inputManager);
	m_world->Step(1.f / 60.f, 6, 2);
}

void GameplayScreen::draw() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.f, 0.f, 0.f, 1.f);

	m_textureProgram.use();

	//tex uniform
	GLint textureUniform = m_textureProgram.getUniformLocation("mySampler");
	glUniform1i(textureUniform, 0);
	glActiveTexture(GL_TEXTURE0);

	//camera matrix
	glm::mat4 projectionMatrix = m_camera.getCameraMatrix();
	GLint pUniform = m_textureProgram.getUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

	m_spriteBatch.begin();

	//draw all the boxes
	for (auto& b : m_boxes) {
		b.draw(m_spriteBatch);
	}
	m_player.draw(m_spriteBatch);
	m_spriteBatch.end();

	m_spriteBatch.renderBatch();

	m_textureProgram.unuse();

	//debug rendering

	if (m_renderDebug) {
		glm::vec4 destRect;
		for (auto& b : m_boxes) {
			destRect.x = b.getBody()->GetPosition().x - b.getDimensions().x / 2.f;
			destRect.y = b.getBody()->GetPosition().y - b.getDimensions().y / 2.f;
			destRect.z = b.getDimensions().x;
			destRect.w = b.getDimensions().y;
			m_debugRenderer.drawBox(destRect, Engine::ColorRGBA8(255, 255, 255, 255), b.getBody()->GetAngle());

		}
		//render player
		m_player.drawDebug(m_debugRenderer);

		m_debugRenderer.end();
		m_debugRenderer.render(projectionMatrix, 2.f);
	}
	Light playerLight;
	playerLight.color = Engine::ColorRGBA8(255, 255, 255, 128);
	playerLight.position = m_player.getPosition();
	playerLight.size = 30.0f;

	Light mouseLight;
	mouseLight.color = Engine::ColorRGBA8(255, 0, 255, 150);
	mouseLight.position = m_camera.convertScreenToWorld(m_game->inputManager.getMouseCoords());
	mouseLight.size = 45.0f;

	m_lightProgram.use();
	pUniform = m_textureProgram.getUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);
	// Additive blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	m_spriteBatch.begin();

	playerLight.draw(m_spriteBatch);
	mouseLight.draw(m_spriteBatch);

	m_spriteBatch.end();
	m_spriteBatch.renderBatch();

	m_lightProgram.unuse();

	// Reset to regular alpha blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_GUI.draw();
}

void GameplayScreen::checkInput() {

	SDL_Event evnt;

	while (SDL_PollEvent(&evnt)) {

		m_game->onSDLEvent(evnt);
		m_GUI.onSDLEvent(evnt);
		switch (evnt.type) {
		case SDL_QUIT:
			onExitClicked(CEGUI::EventArgs());
			break;
		}
	}
}

void GameplayScreen::initUI() {

	//init UI
	m_GUI.init("GUI");
	m_GUI.loadScheme("TaharezLook.scheme");
	m_GUI.setFont("DejaVuSans-10");
	CEGUI::PushButton* testButton = static_cast<CEGUI::PushButton*>(m_GUI.createWidget("TaharezLook/Button", glm::vec4(0.5f, 0.5f, 0.1f, 0.05f), glm::vec4(0.f), "TestButton"));
	testButton->setText("Exit Game!");

	testButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GameplayScreen::onExitClicked, this));

	CEGUI::Combobox* TestCombobox = static_cast<CEGUI::Combobox*>(m_GUI.createWidget("TaharezLook/Combobox", glm::vec4(0.2f, 0.2f, 0.1f, 0.05f), glm::vec4(0.0f), "TestCombobox"));

	m_GUI.setMouseCursor("TaharezLook/MouseArrow");
	m_GUI.showMouseCursor();
	SDL_ShowCursor(0);
}

bool GameplayScreen::onExitClicked(const CEGUI::EventArgs& e) {

	//std::cout << "User Quit\n";
	m_currentState = Engine::ScreenState::EXIT_APPLICATION;

	return true;
}


