#include "Human.h"
#include <random>
#include <ctime>
#include <glm/gtx/rotate_vector.hpp>

Human::Human() :
	_frames(0)
{
}


Human::~Human()
{
}

void Human::init(float speed, glm::vec2 pos)
{
	static std::mt19937 randomEngine(time(nullptr));

	static std::uniform_real_distribution<float> randDir(-1.f, 1.f);

	_color = Bengine::ColorRGBA8(200, 0, 200, 255);

	
	_health = 20;
	_speed = speed;
	_position = pos;
	_direction = glm::vec2(randDir(randomEngine), randDir(randomEngine));
	if (_direction.length() == 0) _direction = glm::vec2(1.f, 0.f);

	_direction = glm::normalize(_direction);
}

void Human::update(const std::vector<std::string>& levelData, std::vector<Human*>& humans, std::vector<Zombie*>& zombies, float deltaTime)
{
	static std::mt19937 randomEngine(time(nullptr));

	static std::uniform_real_distribution<float> randRotate(-40.f, 40.f);

	_position += _direction * _speed * deltaTime;

	if (_frames == 20) {
		_direction = glm::rotate(_direction, randRotate(randomEngine));
		_frames = 0;
	}
	else {
		_frames++;
	}
	if (collideWithLevel(levelData)) {
		_direction = glm::rotate(_direction, randRotate(randomEngine));
	}
}
