#include "EngineErrors.h"
#include <iostream>
#include <cstdlib>
#include <SDL\SDL.h>
namespace Engine {
	void fatalError(std::string errorString) {

		std::cout << errorString << std::endl;
		std::cout << "Enter any key to quit...";
		int tmp;
		std::cin >> tmp;
		SDL_Quit();
		exit(-1);
	}
}