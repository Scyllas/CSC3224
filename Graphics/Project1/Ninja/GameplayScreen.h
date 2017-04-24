#pragma once
#include <SDL\SDL.h>

#include <Engine/IGameScreen.h>
#include <Engine\ResourceManager.h>
#include <Engine\SpriteBatch.h>
#include <Engine\GLSLProgram.h>
#include <Engine\Camera2D.h>
#include <Engine\GLTexture.h>
#include <Engine/IMainGame.h>
#include <Engine\Window.h>
#include <Engine\DebugRenderer.h>
#include <Engine\GUI.h>


#include "ScreenIndices.h"
#include "Box.h"
#include "Light.h"
#include "PlayerChar.h"
#include <vector>
#include <random>

class GameplayScreen : public Engine::IGameScreen{

public:
	GameplayScreen(Engine::Window* window);
	~GameplayScreen();

	virtual int getNextScreenIndex() const override;
	virtual int getPreviousScreenIndex() const override;


	virtual void build() override;
	virtual void destroy() override;


	virtual void onEntry() override;
	virtual void onExit() override;


	virtual void update() override;
	virtual void draw() override;

private:
	void checkInput();
	void initUI();

	bool GameplayScreen::onExitClicked(const CEGUI::EventArgs& e);

	Engine::GLSLProgram m_textureProgram;
	Engine::GLSLProgram m_lightProgram;
	Engine::Camera2D m_camera;
	Engine::SpriteBatch m_spriteBatch;
	Engine::GLTexture m_texture;
	Engine::Window* m_window;
	Engine::DebugRenderer m_debugRenderer;
	Engine::GUI m_GUI;

	bool m_renderDebug = false;

	PlayerChar m_player;
	std::vector<Box> m_boxes;
	std::unique_ptr<b2World> m_world;
};

