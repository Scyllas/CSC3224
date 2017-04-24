#include "Human.h"
#include <random>
#include <ctime>
#include <glm/gtx/rotate_vector.hpp>

Human::Human()
{
}


Human::~Human()
{
}

void Human::init(float speed, glm::vec2 pos)
{
	static std::mt19937 randomEngine(time(nullptr));

	static std::uniform_real_distribution<float> randDir(-1.f, 1.f);

	m_color = Engine::ColorRGBA8(255, 255, 255, 255);
	m_textureID = Engine::ResourceManager::getTexture("Textures/human.png").id;


	m_health = 20;
	m_speed = speed;
	m_position = pos;
	m_direction = glm::vec2(randDir(randomEngine), randDir(randomEngine));
	if (m_direction.length() == 0) m_direction = glm::vec2(1.f, 0.f);

	m_direction = glm::normalize(m_direction);
}

void Human::update(const std::vector<std::string>& levelData, std::vector<Human*>& humans, std::vector<Zombie*>& zombies, float deltaTime)
{
	static std::mt19937 randomEngine(time(nullptr));

	static std::uniform_real_distribution<float> randRotate(-40.f, 40.f);

	m_position += m_direction * m_speed * deltaTime;

	if (m_frames == 20) {
		m_direction = glm::rotate(m_direction, randRotate(randomEngine));
		m_frames = 0;
	}
	else {
		m_frames++;
	}
	if (collideWithLevel(levelData)) {
		m_direction = glm::rotate(m_direction, randRotate(randomEngine));
	}
}
