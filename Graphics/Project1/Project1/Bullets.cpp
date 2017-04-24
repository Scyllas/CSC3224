#include "Bullets.h"
#include <Engine\ResourceManager.h>


Bullets::Bullets(glm::vec2 pos, glm::vec2 dir, float speed, int lifeTime) :
m_lifeTime(lifeTime),
m_position(pos),
m_direction(dir),
m_speed(speed) {
}

Bullets::~Bullets()
{
}


void Bullets::draw(Engine::SpriteBatch & spriteBatch) {


	glm::vec4 uv(0.f, 0.f, 1.f, 1.f);
	static Engine::GLTexture texture = Engine::ResourceManager::getTexture("Textures/jimmyJump_pack/PNG/CharacterRight_Standing.png");
	Engine::ColorRGBA8 color;
	color = Engine::ColorRGBA8(255, 255, 255, 255);


	glm::vec4 posAndSize = glm::vec4(m_position.x, m_position.y, 30, 30);

	spriteBatch.draw(posAndSize, uv, texture.id, 0.f, color);

}

bool Bullets::update() {

	m_position += m_direction * m_speed;
	m_lifeTime--;
	if (m_lifeTime == 0) {
		return true;
	}
	else {
		false;
	}
}
