#include "Gun.h"



Gun::Gun(std::string name, int firerate, int bulletsPerShot, float spread, float bulletDamage, float bulletSpeed, Engine::SoundEffect fireEffect) :
	m_name(name),
	m_fireRate(firerate),
	m_bulletsPerShot(bulletsPerShot),
	m_spread(spread),
	m_bulletDamage(bulletDamage),
	m_bulletSpeed(bulletSpeed),
	m_frameCounter(0),
	m_fireEffect(fireEffect)


{
}


Gun::~Gun() {



}

void Gun::update(bool isMouseDown, const glm::vec2& position, const glm::vec2& direction, std::vector<Bullet>& bullets, float deltaTime) {

	m_frameCounter += 1.f * deltaTime;
	if (m_frameCounter >= m_fireRate && isMouseDown) {
		fire(direction, position, bullets);
		m_frameCounter = 0;
	}
}

void Gun::fire(const glm::vec2& direction, const glm::vec2& position, std::vector<Bullet>& bullets) {

	static std::mt19937 randomEngine(time(nullptr));

	static std::uniform_real_distribution<float> randRotate(-m_spread, m_spread);

	m_fireEffect.play();

	for (int i = 0; i < m_bulletsPerShot; i++) {
		bullets.emplace_back(position,
			glm::rotate(direction, randRotate(randomEngine) * RAND_TO_DEGREES),
			m_bulletDamage,
			m_bulletSpeed);
	}
}
