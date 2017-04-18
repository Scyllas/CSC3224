#include "ParticleBatch2D.h"

namespace Bengine {

	ParticleBatch2D::ParticleBatch2D() {


	}


	ParticleBatch2D::~ParticleBatch2D() {

		delete[] m_Particles;

	}

	void ParticleBatch2D::init(
		int maxParticles,
		float decayRate,
		GLTexture texture,
		std::function<void(Particle2D&, float)> updateFunc /* = defaultParticleUpdate*/){

		m_maxParticles = maxParticles;
		m_Particles = new Particle2D[maxParticles];
		m_decayRate = decayRate;
		m_texture = texture;
		m_updateFunc = updateFunc;
	}

	void ParticleBatch2D::update(float deltaTime) {

		for (int i = 0; i < m_maxParticles; i++) {
			if (m_Particles[i].life > 0.f) {
				m_updateFunc(m_Particles[i], deltaTime);
				m_Particles[i].life -= m_decayRate * deltaTime;

			}
		}

	}

	void ParticleBatch2D::draw(SpriteBatch* spriteBatch) {

		glm::vec4 uvRect(0.f, 0.f, 1.f, 1.f);

		for (int i = 0; i < m_maxParticles; i++) {

			auto& p = m_Particles[i];
			if (p.life > 0.f) {

				glm::vec4 destRect(
					p.position.x,
					p.position.y,
					p.width,
					p.width);

				spriteBatch->draw(
					destRect,
					uvRect,
					m_texture.id, 
					0.f, 
					p.color);

			}
		}
	}

	void ParticleBatch2D::addParticle(
		const glm::vec2 & position, 
		const glm::vec2 & velocity, 
		const ColorRGBA8 & color,
		float width) {

		int particleIndex = findFreeParticle();

		auto &p = m_Particles[particleIndex];

		p.life = 1.f;
		p.position = position;
		p.velocity = velocity;
		p.color = color;
		p.width = width;


	}

	int ParticleBatch2D::findFreeParticle(){
		
		for (int i = m_lastFreeParticle; i < m_maxParticles; i++) {
			if (m_Particles[i].life <= 0.f) {
				m_lastFreeParticle = i;
				return i;
			}
		}
		for (int i = 0; i < m_maxParticles; i++) {
			if (m_Particles[i].life <= 0.f) {
				m_lastFreeParticle = i;
				return i;
			}
		}
		return 0;
	}



}