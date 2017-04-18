#pragma once
#include <vector>

#include "IGameScreen.h"

namespace Bengine {

	class IMainGame;
	class IGameScreen;

	class ScreenList
	{
	public:

		ScreenList(IMainGame* game);
		~ScreenList();

		IGameScreen* moveNext();
		IGameScreen* movePrevious();

		void setScreen(int nextScreen);
		void addScreen(IGameScreen* newScreen);


		IGameScreen* getCurrent();

		void destroy();

	protected:
		IMainGame* m_game = nullptr;
		std::vector<IGameScreen*> m_screens;
		int m_currentScreenIndex = -1;
	};

}