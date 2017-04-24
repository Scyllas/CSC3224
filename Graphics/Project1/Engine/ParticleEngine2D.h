#pragma once

#include <vector>
#include "ParticleBatch2D.h"
#include "SpriteBatch.h"


namespace Engine {

	class ParticleEngine2D
	{
	public:
		ParticleEngine2D();
		~ParticleEngine2D();

		//after adding batch, engine is responsible for deallocation
		void addParticleBatch(ParticleBatch2D* particleBatch);

		void update(float deltaTime);

		void draw(SpriteBatch* spriteBatch);

	private:
		std::vector<ParticleBatch2D*> m_batches;
	};

}