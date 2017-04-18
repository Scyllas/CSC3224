#pragma once
#include <SDL\SDL.h>

#include <Bengine/IGameScreen.h>
#include <Bengine\ResourceManager.h>
#include <Bengine\SpriteBatch.h>
#include <Bengine\GLSLProgram.h>
#include <Bengine\Camera2D.h>
#include <Bengine\GLTexture.h>
#include <Bengine/IMainGame.h>
#include <Bengine\Window.h>
#include <Bengine\DebugRenderer.h>
#include <Bengine\GUI.h>

#include "ScreenIndices.h"
#include "Box.h"
#include "Light.h"
#include "PlayerChar.h"
#include <vector>
#include <random>

class GameplayScreen : public Bengine::IGameScreen{

public:
	GameplayScreen(Bengine::Window* window);
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

	Bengine::GLSLProgram m_textureProgram;
	Bengine::GLSLProgram m_lightProgram;
	Bengine::Camera2D m_camera;
	Bengine::SpriteBatch m_spriteBatch;
	Bengine::GLTexture m_texture;
	Bengine::Window* m_window;
	Bengine::DebugRenderer m_debugRenderer;
	Bengine::GUI m_GUI;

	bool m_renderDebug = false;

	PlayerChar m_player;
	std::vector<Box> m_boxes;
	std::unique_ptr<b2World> m_world;
};

