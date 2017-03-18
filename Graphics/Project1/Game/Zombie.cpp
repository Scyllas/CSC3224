#include "Zombie.h"
#include "Human.h"


Zombie::Zombie()
{
}


Zombie::~Zombie()
{
}

void Zombie::init(float speed, glm::vec2 pos)
{
	m_health = 150;
	m_speed = speed;
	m_position = pos;
	m_color = Bengine::ColorRGBA8(0, 160, 0, 255);
}

void Zombie::update(const std::vector<std::string>& levelData,
	std::vector<Human*>& humans,
	std::vector<Zombie*>& zombies,
	float deltaTime) {

	Human* closestHuman = getNearestHuman(humans);

	if (closestHuman != nullptr) {
		glm::vec2 direction = glm::normalize(closestHuman->getPosition() - m_position);
		m_position += direction * m_speed * deltaTime;
	}

	collideWithLevel(levelData);
}

Human* Zombie::getNearestHuman(std::vector<Human*>& humans) {

	Human* closestHuman = nullptr;

	float smallestDistance = 9999999.f;

	for (int i = 0; i < humans.size(); i++) {

		glm::vec2 distVec = humans[i]->getPosition() - m_position;

		float distance = glm::length(distVec);

		if (distance < smallestDistance) {

			smallestDistance = distance;
			closestHuman = humans[i];

		}
	}
	return closestHuman;
}
