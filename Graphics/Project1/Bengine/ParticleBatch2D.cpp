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
		GLTexture texture) {

		m_maxParticles = maxParticles;
		m_Particles = new Particle2D[maxParticles];
		m_decayRate = decayRate;
		m_texture = texture;

	}

	void ParticleBatch2D::update(float deltaTime) {

		for (int i = 0; i < m_maxParticles; i++) {
			if (m_Particles[i].m_life > 0.f) {
				m_Particles[i].update(deltaTime);
				m_Particles[i].m_life -= m_decayRate * deltaTime;

			}
		}

	}

	void ParticleBatch2D::draw(SpriteBatch* spriteBatch) {

		glm::vec4 uvRect(0.f, 0.f, 1.f, 1.f);

		for (int i = 0; i < m_maxParticles; i++) {

			auto& p = m_Particles[i];
			if (p.m_life > 0.f) {

				glm::vec4 destRect(
					p.m_position.x,
					p.m_position.y,
					p.m_width,
					p.m_width);

				spriteBatch->draw(
					destRect,
					uvRect,
					m_texture.id, 
					0.f, 
					p.m_color);

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

		p.m_life = 1.f;
		p.m_position = position;
		p.m_velocity = velocity;
		p.m_color = color;
		p.m_width = width;


	}

	int ParticleBatch2D::findFreeParticle(){
		
		for (int i = m_lastFreeParticle; i < m_maxParticles; i++) {
			if (m_Particles[i].m_life <= 0.f) {
				m_lastFreeParticle = i;
				return i;
			}
		}
		for (int i = 0; i < m_maxParticles; i++) {
			if (m_Particles[i].m_life <= 0.f) {
				m_lastFreeParticle = i;
				return i;
			}
		}
		return 0;
	}

	void Particle2D::update(float deltaTime) {

		m_position += m_velocity* deltaTime;

	}

}