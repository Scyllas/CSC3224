#pragma once

#include <glm\glm.hpp>
#include <Bengine\SpriteBatch.h>
#include <Bengine\ResourceManager.h>

#include "Human.h"
#include "Zombie.h"
#include "Agent.h"
#include "Level.h"

class Human;
class Zombie;
class Agent;

const int BULLET_RADIUS = 5;

class Bullet
{
public:
	Bullet(glm::vec2 position, glm::vec2 direction, float damage, float speed);
	~Bullet();

	bool collideWithAgent(Agent* agent);

	bool update(const std::vector<std::string>& levelData, float deltaTime);

	void draw(Bengine::SpriteBatch& spriteBatch);

	float getDamage() const { return _damage; }

private:

	bool collideWithWorld(const std::vector<std::string>& levelData);

	float _damage;
	float _speed;
	glm::vec2 _direction;
	glm::vec2 _position;
};

