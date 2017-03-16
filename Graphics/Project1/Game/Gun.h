#pragma once
#include <string>
#include <vector>
#include <glm\glm.hpp>
#include "Bullet.h"
#include <ctime>
#include <random>
#include <glm\gtx\rotate_vector.hpp>

const float RAND_TO_DEGREES = 3.14 / 180;
class Gun
{
public:
	Gun(std::string name, int firerate, int bulletsPerShot, float spread, float _bulletDamage, float _bulletSpeed);
	~Gun();

	void update(bool isMouseDown, const glm::vec2& position, const glm::vec2& direction, std::vector<Bullet>& bullets, float deltaTime);



private:

	void fire(const glm::vec2& direction, const glm::vec2& position, std::vector<Bullet>& bullets);

	std::string _name;

	int _fireRate; //frames, not time
	int _bulletsPerShot;

	float _spread;

	float _bulletSpeed;
	float _bulletDamage;

	float _frameCounter;


};

