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

	float getDamage() const { return m_damage; }

	glm::vec2 getPosition() const { return m_position; }

private:

	bool collideWithWorld(const std::vector<std::string>& levelData);

	float m_damage;
	float m_speed;
	glm::vec2 m_direction;
	glm::vec2 m_position;
};

