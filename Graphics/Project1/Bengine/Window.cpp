#include "Window.h"
#include "BengineErrors.h"

namespace Bengine {
	Window::Window()
	{
	}


	Window::~Window()
	{
	}

	int Window::create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags)
	{

		Uint32 flags = SDL_WINDOW_OPENGL;

		if (currentFlags & INVISIBLE) {
			flags |= SDL_WINDOW_HIDDEN;
		}
		if (currentFlags & FULLSCREEN) {
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		}
		if (currentFlags & BORDERLESS) {
			flags |= SDL_WINDOW_BORDERLESS;
		}

		m_sdlWindow = SDL_CreateWindow(windowName.c_str(),
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			screenWidth, screenHeight,
			flags);

		if (m_sdlWindow == nullptr) {
			fatalError("Window could not be created!");
		}

		SDL_GLContext glContext = SDL_GL_CreateContext(m_sdlWindow);

		if (glContext == nullptr) {
			fatalError("SDL_GL context could not be created");
		}
		GLenum error = glewInit();
		if (error != GLEW_OK) {
			fatalError("could not initialise glew");
		}

		//check openGLversion
		std::printf("*** OpenGL Version: %s *** \n", glGetString(GL_VERSION));

		//normalised RGBA
		glClearColor(0.f, 0.f, 1.f, 1.0);

		//vsync toggle
		SDL_GL_SetSwapInterval(0);

		//enable alpha blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

		return 0;
	}

	void Window::swapBuffer()
	{
		SDL_GL_SwapWindow(m_sdlWindow);
	}
}