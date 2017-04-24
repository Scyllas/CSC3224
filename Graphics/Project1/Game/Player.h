#pragma once
#include "Human.h"
#include <Engine/InputManager.h>
#include <SDL\SDL.h>
#include <Engine\Camera2D.h>
#include <Engine\ResourceManager.h>

#include "Bullet.h"
#include "Gun.h"

class Bullet;
class Gun;

class Player :public Human
{
public:
	Player();
	~Player();

	void init(float speed, glm::vec2 pos, Engine::InputManager* inputManager, Engine::Camera2D* camera, std::vector<Bullet>*bullets);

	void addGun(Gun* gun);

	void update(const std::vector<std::string>& levelData,
		std::vector<Human*>& humans,
		std::vector<Zombie*>& zombies,
		float deltaTime) override;


private:

	std::vector<Gun*> m_guns;
	int m_currentGunIndex = -1;
	Engine::InputManager* m_inputManager;
	Engine::Camera2D* m_camera;

	std::vector<Bullet>* m_bullets;
};

