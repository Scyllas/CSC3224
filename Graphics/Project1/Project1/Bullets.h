#pragma once
#include <glm\glm.hpp>
#include <Bengine\SpriteBatch.h>


class Bullets
{
public:
	Bullets(glm::vec2 pos, glm::vec2 dir, float speed, int lifeTime);
	~Bullets();

	glm::vec2 getPosition() { return m_position; }

	void draw(Bengine::SpriteBatch& spriteBatch);
	bool update();//returns true on death

private:
	int m_lifeTime;
	float m_speed;
	glm::vec2 m_direction;
	glm::vec2 m_position;
};

