#pragma once
#include <unordered_map>
#include <glm\glm.hpp>

namespace Engine {
	
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

		inline glm::vec2 getMouseCoords() const { return m_mouseCoords; };
	private:

		//just pressed
		bool wasKeyDown(unsigned int keyID);

		
		glm::vec2 m_mouseCoords = glm::vec2(0.f);
		std::unordered_map<unsigned int, bool> m_keyMap;
		std::unordered_map<unsigned int, bool> m_previousKeyMap;


	};

}