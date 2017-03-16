#include "Player.h"



Player::Player() :
	_currentGunIndex(-1)
{
}


Player::~Player()
{
}

void Player::init(float speed, glm::vec2 pos, Bengine::InputManager* inputManager, Bengine::Camera2D* camera, std::vector<Bullet>* bullets) {

	_health = 150;
	_camera = camera;
	_speed = speed;
	_bullets = bullets;
	_position = pos;
	_inputManager = inputManager;

	_color = Bengine::ColorRGBA8(0, 0, 185, 255);

}

void Player::addGun(Gun * gun)
{
	_guns.push_back(gun);

	if (_currentGunIndex == -1) {
		_currentGunIndex = 0;
		//give player first gun
	}
}

void Player::update(const std::vector<std::string>& levelData,
	std::vector<Human*>& humans,
	std::vector<Zombie*>& zombies,
	float deltaTime) {

	if (_inputManager->isKeyDown(SDLK_w)) {
		_position.y += _speed * deltaTime;
	}
	else if (_inputManager->isKeyDown(SDLK_s)) {
		_position.y -= _speed* deltaTime;
	}
	if (_inputManager->isKeyDown(SDLK_a)) {
		_position.x -= _speed* deltaTime;
	}
	else if (_inputManager->isKeyDown(SDLK_d)) {
		_position.x += _speed* deltaTime;
	}

	if (_inputManager->isKeyDown(SDLK_1) && _guns.size() >= 0) {
		_currentGunIndex = 0;
	}
	else if (_inputManager->isKeyDown(SDLK_2) && _guns.size() >= 1) {
		_currentGunIndex = 1;
	}
	else if (_inputManager->isKeyDown(SDLK_3) && _guns.size() >= 2) {
		_currentGunIndex = 2;
	}

	if (_currentGunIndex != -1) {


		glm::vec2 centerPosition = _position + glm::vec2(AGENT_RADIUS);
		glm::vec2 mouseCoords = _inputManager->getMouseCoords();
		mouseCoords = _camera->convertScreenToWorld(mouseCoords);
		glm::vec2 direction = normalize(mouseCoords - centerPosition);
		_guns[_currentGunIndex]->update(
			_inputManager->isKeyDown(SDL_BUTTON_LEFT),
			centerPosition,
			direction,
			*_bullets, 
			deltaTime);
	}

	collideWithLevel(levelData);
}
