#include "MainMenuScreen.h"

MainMenuScreen::MainMenuScreen(Engine::Window* window) : m_window(window) {
	m_screenIndex = SCREEN_INDEX_MAINMENU;
}

MainMenuScreen::~MainMenuScreen() {
}

int MainMenuScreen::getNextScreenIndex() const {
	return m_nextScreenIndex;
}

int MainMenuScreen::getPreviousScreenIndex() const {
	return SCREEN_INDEX_NO_SCREEN;
}

void MainMenuScreen::build() {

}

void MainMenuScreen::destroy() {

}

void MainMenuScreen::onEntry() {
	// Init camera
	m_camera.init(m_window->getScreenWidth(), m_window->getScreenHeight());
	m_camera.setScale(32.0f);

	initUI();

	m_audioEngine.init();
	Engine::Music music = m_audioEngine.loadMusic("Sound/XYZ.ogg");
	music.play(-1);
}

void MainMenuScreen::onExit() {
	m_GUI.destroy();
}

void MainMenuScreen::update() {
	m_camera.update();
	checkInput();
}

void MainMenuScreen::draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.2f, 1.0f);

	m_GUI.draw();
}

void MainMenuScreen::initUI() {
	// Init the UI
	m_GUI.init("GUI");
	m_GUI.loadScheme("TaharezLook.scheme");
	m_GUI.setFont("DejaVuSans-10");

	CEGUI::PushButton* playGameButton = static_cast<CEGUI::PushButton*>(m_GUI.createWidget("TaharezLook/Button", glm::vec4(0.45f, 0.5f, 0.1f, 0.05f), glm::vec4(0.0f), "NewGameButton"));
	playGameButton->setText("New Game");
	// Set up event to be called when we click
	playGameButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&MainMenuScreen::onNewGameClicked, this));

	CEGUI::PushButton* editorButton = static_cast<CEGUI::PushButton*>(m_GUI.createWidget("TaharezLook/Button", glm::vec4(0.45f, 0.56f, 0.1f, 0.05f), glm::vec4(0.0f), "EditorButton"));
	editorButton->setText("Level Editor");
	// Set up event to be called when we click
	editorButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&MainMenuScreen::onEditorClicked, this));

	CEGUI::PushButton* exitButton = static_cast<CEGUI::PushButton*>(m_GUI.createWidget("TaharezLook/Button", glm::vec4(0.45f, 0.62f, 0.1f, 0.05f), glm::vec4(0.0f), "ExitButton"));
	exitButton->setText("Exit Game");
	// Set the event to be called when we click
	exitButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&MainMenuScreen::onExitClicked, this));

	m_GUI.setMouseCursor("TaharezLook/MouseArrow");
	m_GUI.showMouseCursor();
	SDL_ShowCursor(0);
}

void MainMenuScreen::checkInput() {
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt)) {
		m_GUI.onSDLEvent(evnt);
		switch (evnt.type) {
		case SDL_QUIT:
			onExitClicked(CEGUI::EventArgs());
			break;
		}
	}
}

bool MainMenuScreen::onNewGameClicked(const CEGUI::EventArgs& e) {
	m_nextScreenIndex = SCREEN_INDEX_GAMEPLAY;
	m_currentState = Engine::ScreenState::CHANGE_NEXT;
	return true;
}

bool MainMenuScreen::onEditorClicked(const CEGUI::EventArgs& e) {
	m_nextScreenIndex = SCREEN_INDEX_EDITOR;
	m_currentState = Engine::ScreenState::CHANGE_NEXT;
	return true;
}

bool MainMenuScreen::onExitClicked(const CEGUI::EventArgs& e) {
	m_currentState = Engine::ScreenState::EXIT_APPLICATION;
	return true;
}