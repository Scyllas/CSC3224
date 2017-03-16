#include "Bullets.h"
#include <Bengine\ResourceManager.h>


Bullets::Bullets(glm::vec2 pos, glm::vec2 dir, float speed, int lifeTime) :
_lifeTime(lifeTime),
_position(pos),
_direction(dir),
_speed(speed) {
}

Bullets::~Bullets()
{
}


void Bullets::draw(Bengine::SpriteBatch & spriteBatch) {


	glm::vec4 uv(0.f, 0.f, 1.f, 1.f);
	static Bengine::GLTexture texture = Bengine::ResourceManager::getTexture("Textures/jimmyJump_pack/PNG/CharacterRight_Standing.png");
	Bengine::ColorRGBA8 color;
	color = Bengine::ColorRGBA8(255, 255, 255, 255);


	glm::vec4 posAndSize = glm::vec4(_position.x, _position.y, 30, 30);

	spriteBatch.draw(posAndSize, uv, texture.id, 0.f, color);

}

bool Bullets::update() {

	_position += _direction * _speed;
	_lifeTime--;
	if (_lifeTime == 0) {
		return true;
	}
	else {
		false;
	}
}
