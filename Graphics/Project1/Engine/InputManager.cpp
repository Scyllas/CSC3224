#include "InputManager.h"

namespace Engine {

	InputManager::InputManager()
	{
	}


	InputManager::~InputManager()
	{
	}

	void InputManager::update()	{

		//loop through keymap, copying to previous keymap
		for (auto& it : m_keyMap) {
			m_previousKeyMap[it.first] = it.second;
		}
	}

	void InputManager::pressKey(unsigned int keyID)
	{

		m_keyMap[keyID] = true;
	}

	void InputManager::releaseKey(unsigned int keyID)
	{
		m_keyMap[keyID] = false;
	}

	void InputManager::setMouseCoords(float x, float y)	{

		m_mouseCoords.x = x;

		m_mouseCoords.y = y;
	}

	bool InputManager::isKeyPressed(unsigned int keyID)	{

		//if pressed this frame, but not last
		if (isKeyDown(keyID) == true && wasKeyDown(keyID) == false) {
			return true;
		}
		return false;
	}

	bool InputManager::isKeyDown(unsigned int keyID)
	{
		auto it = m_keyMap.find(keyID);
		if (it != m_keyMap.end()) {
			return it->second;
		}
		else {
			return false;
		}
	}

	bool InputManager::wasKeyDown(unsigned int keyID){

		auto it = m_previousKeyMap.find(keyID);
		if (it != m_previousKeyMap.end()) {
			return it->second;
		}
		else {
			return false;
		}
	}


}