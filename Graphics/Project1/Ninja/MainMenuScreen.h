#pragma once

#include "PlayerChar.h"
#include "ScreenIndices.h"

#include <Engine/IGameScreen.h>
#include <vector>
#include <Engine/SpriteBatch.h>
#include <Engine/GLSLProgram.h>
#include <Engine/Camera2D.h>
#include <Engine/GLTexture.h>
#include <Engine/Window.h>
#include <Engine/DebugRenderer.h>
#include <Engine\AudioEngine.h>

#include <Engine/GUI.h>

class MainMenuScreen : public Engine::IGameScreen {
public:
	MainMenuScreen(Engine::Window* window);
	~MainMenuScreen();

	virtual int getNextScreenIndex() const override;

	virtual int getPreviousScreenIndex() const override;

	virtual void build() override;

	virtual void destroy() override;

	virtual void onEntry() override;

	virtual void onExit() override;

	virtual void update() override;

	virtual void draw() override;

private:
	void initUI();
	void checkInput();

	bool onNewGameClicked(const CEGUI::EventArgs& e);
	bool onEditorClicked(const CEGUI::EventArgs& e);
	bool onExitClicked(const CEGUI::EventArgs& e);

	int m_nextScreenIndex = SCREEN_INDEX_GAMEPLAY;
	Engine::Camera2D m_camera;
	Engine::Window* m_window;
	Engine::GUI m_GUI;
	Engine::AudioEngine m_audioEngine;
};

