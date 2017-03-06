#include "Bengine.h"
#include <SDL/SDL.h>
#include <GL/glew.h>
namespace Bengine {
	int init() {
		//brings sdl into code
		SDL_Init(SDL_INIT_EVERYTHING);

		//draw to one screen while clearing to another, and swapping between
		//the two screens
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		return 0;
	}
}