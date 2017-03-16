#pragma once
#include <glm\glm.hpp>
#include <Bengine\SpriteBatch.h>


class Bullets
{
public:
	Bullets(glm::vec2 pos, glm::vec2 dir, float speed, int lifeTime);
	~Bullets();

	glm::vec2 getPosition() { return _position; }

	void draw(Bengine::SpriteBatch& spriteBatch);
	bool update();//returns true on death

private:
	int _lifeTime;
	float _speed;
	glm::vec2 _direction;
	glm::vec2 _position;
};

