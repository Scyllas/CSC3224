#pragma once
#include "Human.h"
#include <Bengine/InputManager.h>
#include <SDL\SDL.h>
#include <Bengine\Camera2D.h>

#include "Bullet.h"
#include "Gun.h"

class Bullet;
class Gun;

class Player :public Human
{
public:
	Player();
	~Player();

	void init(float speed, glm::vec2 pos, Bengine::InputManager* inputManager, Bengine::Camera2D* camera, std::vector<Bullet>*bullets);

	void addGun(Gun* gun);

	void update(const std::vector<std::string>& levelData,
		std::vector<Human*>& humans,
		std::vector<Zombie*>& zombies,
		float deltaTime) override;


private:

	std::vector<Gun*> _guns;
	int _currentGunIndex;
	Bengine::InputManager* _inputManager;
	Bengine::Camera2D* _camera;

	std::vector<Bullet>* _bullets;
};

