#pragma once

#define SCREEN_INDEX_NO_SCREEN -1

namespace Bengine {

	class IMainGame;

	enum class ScreenState
	{
		NONE,
		RUNNING,
		EXIT_APPLICATION,
		CHANGE_NEXT,
		CHANGE_PREVIOUS
	};
	class IGameScreen
	{
	public:
		friend class ScreenList;
		IGameScreen() {
			//blank
		}
		virtual ~IGameScreen() {
			//blank
		}

		//returns the index for the next and previous screens
		virtual int getNextScreenIndex() const = 0;
		virtual int getPreviousScreenIndex() const = 0;

		//called at begninning and end
		virtual void build() = 0;
		virtual void destroy() = 0;

		//called when screen enters and exits focus
		virtual void onEntry() = 0;
		virtual void onExit() = 0;

		//main game loop functions
		virtual void update() = 0;
		virtual void draw() = 0;

		inline int getScreenIndex() const { return m_screenIndex; }

		inline void setRunning() { m_currentState = ScreenState::RUNNING; }

		ScreenState getState() const { return m_currentState; }

		inline void setParentGame(IMainGame* game) { m_game = game; }

	protected:
		ScreenState m_currentState = ScreenState::NONE;
		IMainGame* m_game = nullptr;
		int m_screenIndex = SCREEN_INDEX_NO_SCREEN;
	};

}