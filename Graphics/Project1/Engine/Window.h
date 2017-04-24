#pragma once

#include<SDL/SDL.h>
#include<GL/glew.h>

#include <string>
namespace Engine {
	enum WindowFlags { INVISIBLE = 0x1, FULLSCREEN = 0x2, BORDERLESS = 0x4 };

	class Window
	{
	public:
		Window();
		~Window();

		int create(std::string windowName, int screenWidth, int screeenHeight, unsigned int currentFlags);

		void swapBuffer();

		int getScreenWidth() { return m_screenWidth; }
		int getScreenHeight() { return m_screenHeight; }
	private:

		SDL_Window* m_sdlWindow;
		int m_screenWidth, m_screenHeight;
	};

}