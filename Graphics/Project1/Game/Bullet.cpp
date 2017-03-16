#include "Bullet.h"

Bullet::Bullet(glm::vec2 position, glm::vec2 direction, float damage, float speed) :
	_position(position),
	_direction(direction),
	_damage(damage),
	_speed(speed)
{
}

Bullet::~Bullet()
{
}

bool Bullet::collideWithAgent(Agent * agent)
{
	const float MIN_DISTANCE = AGENT_RADIUS + BULLET_RADIUS;

	glm::vec2 centerPosA = _position;

	glm::vec2 centerPosB = agent->getPosition() + glm::vec2(AGENT_RADIUS);

	glm::vec2 distVec = centerPosA - centerPosB;

	float distance = glm::length(distVec);

	float collisionDepth = MIN_DISTANCE - distance;
	if (collisionDepth > 0) {
		return true;
	}
	return false;
}

void Bullet::draw(Bengine::SpriteBatch& spriteBatch) {

	glm::vec4 destRect(
		_position.x + BULLET_RADIUS,
		_position.y + BULLET_RADIUS,
		BULLET_RADIUS * 2,
		BULLET_RADIUS * 2);
	glm::vec4 uvRect(0.f, 0.f, 1.f, 1.f);
	Bengine::ColorRGBA8 color = Bengine::ColorRGBA8(75, 75, 75, 255);

	spriteBatch.draw(destRect,
		uvRect,
		Bengine::ResourceManager::getTexture("Textures/circle.png").id,
		0.f,
		color);
}

bool Bullet::collideWithWorld(const std::vector<std::string>& levelData)
{
	glm::ivec2 gridPosition;
	gridPosition.x = floor(_position.x / (float)TILE_WIDTH);
	gridPosition.y = floor(_position.y / (float)TILE_WIDTH);

	if (gridPosition.x < 0 || gridPosition.x >= levelData[0].size() ||
		gridPosition.y < 0 || gridPosition.y >= levelData.size()) {
		return true;
	}
	return (levelData[gridPosition.y][gridPosition.x] != '.');


}


bool Bullet::update(const std::vector<std::string>& levelData, float deltaTime)
{

	_position += _direction * _speed * deltaTime;

	return collideWithWorld(levelData);
}
