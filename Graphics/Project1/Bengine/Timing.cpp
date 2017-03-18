#include "Timing.h"

#include <SDL\SDL.h>
namespace Bengine {



	FpsLimiter::FpsLimiter()	{



	}

	void FpsLimiter::init(float maxFPS)	{

		setMaxFPS(maxFPS);

	}

	void FpsLimiter::setMaxFPS(float maxFPS)	{

		m_maxFPS = maxFPS;

	}

	void FpsLimiter::begin()	{

		m_startTicks = SDL_GetTicks();

	}

	float FpsLimiter::end()	{
	
		calculateFPS();
		//limit fps
		float frameTicks = SDL_GetTicks() - m_startTicks;
		if (1000.f / m_maxFPS > frameTicks) {
			SDL_Delay((1000.f / m_maxFPS) - frameTicks);
		}
		return m_fps;

	}

	void FpsLimiter::calculateFPS()	{

		static const int NUMm_SAMPLES = 10;
		static float frameTimes[NUMm_SAMPLES];
		static int currentFrame = 0;

		static float prevTicks = SDL_GetTicks();

		float currentTicks;
		currentTicks = SDL_GetTicks();

		m_frameTime = currentTicks - prevTicks;
		frameTimes[currentFrame % NUMm_SAMPLES] = m_frameTime;

		prevTicks = currentTicks;

		int count;

		currentFrame++;

		if (currentFrame < NUMm_SAMPLES) {
			count = currentFrame;
		}
		else {
			count = NUMm_SAMPLES;
		}

		float frameTimeAverage = 0;
		for (int i = 0; i < count; i++) {
			frameTimeAverage += frameTimes[i];
		}
		frameTimeAverage /= count;

		if (frameTimeAverage > 0) {
			m_fps = 1000.f / frameTimeAverage;
		}
		else {
			m_fps = 60.f;
		}

	}

}