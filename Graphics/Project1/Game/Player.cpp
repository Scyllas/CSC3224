#include "Player.h"



Player::Player()
{
}


Player::~Player()
{
}

void Player::init(float speed, glm::vec2 pos, Engine::InputManager* inputManager, Engine::Camera2D* camera, std::vector<Bullet>* bullets) {

	m_health = 150;
	m_camera = camera;
	m_speed = speed;
	m_bullets = bullets;
	m_position = pos;
	m_inputManager = inputManager;

	m_color = Engine::ColorRGBA8(255, 255, 255, 255);
	m_textureID = Engine::ResourceManager::getTexture("Textures/player.png").id;

}

void Player::addGun(Gun * gun)
{
	m_guns.push_back(gun);

	if (m_currentGunIndex == -1) {
		m_currentGunIndex = 0;
		//give player first gun
	}
}

void Player::update(const std::vector<std::string>& levelData,
	std::vector<Human*>& humans,
	std::vector<Zombie*>& zombies,
	float deltaTime) {

	if (m_inputManager->isKeyDown(SDLK_w)) {
		m_position.y += m_speed * deltaTime;
	}
	else if (m_inputManager->isKeyDown(SDLK_s)) {
		m_position.y -= m_speed* deltaTime;
	}
	if (m_inputManager->isKeyDown(SDLK_a)) {
		m_position.x -= m_speed* deltaTime;
	}
	else if (m_inputManager->isKeyDown(SDLK_d)) {
		m_position.x += m_speed* deltaTime;
	}

	if (m_inputManager->isKeyDown(SDLK_1) && m_guns.size() >= 0) {
		m_currentGunIndex = 0;
	}
	else if (m_inputManager->isKeyDown(SDLK_2) && m_guns.size() >= 1) {
		m_currentGunIndex = 1;
	}
	else if (m_inputManager->isKeyDown(SDLK_3) && m_guns.size() >= 2) {
		m_currentGunIndex = 2;
	}

	glm::vec2 centerPosition = m_position + glm::vec2(AGENT_RADIUS);
	glm::vec2 mouseCoords = m_inputManager->getMouseCoords();
	mouseCoords = m_camera->convertScreenToWorld(mouseCoords);
	m_direction = normalize(mouseCoords - centerPosition);

	if (m_currentGunIndex != -1) {

		m_guns[m_currentGunIndex]->update(
			m_inputManager->isKeyDown(SDL_BUTTON_LEFT),
			centerPosition,
			m_direction,
			*m_bullets,
			deltaTime);
	}

	collideWithLevel(levelData);
}

