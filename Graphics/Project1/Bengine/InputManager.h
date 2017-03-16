#pragma once
#include <unordered_map>
#include <glm\glm.hpp>

namespace Bengine {
	
	class InputManager
	{
	public:
		InputManager();
		~InputManager();

		void update();

		void pressKey(unsigned int keyID);
		void releaseKey(unsigned int keyID);

		void setMouseCoords(float x, float y);

		//just pressed
		bool isKeyPressed(unsigned int keyID);


		//held down
		bool isKeyDown(unsigned int keyID);

		inline glm::vec2 getMouseCoords() const { return _mouseCoords; };
	private:

		//just pressed
		bool wasKeyDown(unsigned int keyID);

		
		glm::vec2 _mouseCoords;
		std::unordered_map<unsigned int, bool> _keyMap;
		std::unordered_map<unsigned int, bool> _previousKeyMap;


	};

}