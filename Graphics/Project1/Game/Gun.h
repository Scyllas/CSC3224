#pragma once
#include <string>
#include <vector>
#include <glm\glm.hpp>
#include "Bullet.h"
#include <ctime>
#include <random>
#include <glm\gtx\rotate_vector.hpp>
#include <Bengine\AudioEngine.h>

const float RAND_TO_DEGREES = 3.14 / 180;
class Gun
{
public:
	Gun(std::string name, int firerate, int bulletsPerShot, float spread, float m_bulletDamage, float m_bulletSpeed, Bengine::SoundEffect fireEffect);
	~Gun();

	void update(bool isMouseDown, const glm::vec2& position, const glm::vec2& direction, std::vector<Bullet>& bullets, float deltaTime);



private:

	Bengine::SoundEffect m_fireEffect;

	void fire(const glm::vec2& direction, const glm::vec2& position, std::vector<Bullet>& bullets);

	std::string m_name;

	int m_fireRate; //frames, not time
	int m_bulletsPerShot;

	float m_spread;

	float m_bulletSpeed;
	float m_bulletDamage;

	float m_frameCounter;


};

