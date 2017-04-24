#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Engine {
	class Camera2D
	{
	public:
		Camera2D();
		~Camera2D();

		void update();
		void init(int screenWidth, int screenHeight);

		glm::vec2 convertScreenToWorld(glm::vec2 screenCoords);

		bool isBoxInView(const glm::vec2& position, const glm::vec2& dimensions);

		void offsetPosition(const glm::vec2& offset) { m_position += offset; m_needsMatrixUpdate = true; }
		void offsetScale(float offset) { m_scale += offset; if (m_scale < 0.001f) m_scale = 0.001f; m_needsMatrixUpdate = true; }

		void setPosition(const glm::vec2 newPosition) { m_position = newPosition; m_needsMatrixUpdate = true; }
		void setScale(float newScale) { m_scale = newScale; m_needsMatrixUpdate = true; }

		inline float getScale() { return m_scale; }
		inline glm::vec2 getPosition() { return m_position; }
		inline glm::mat4 getCameraMatrix() { return m_cameraMatrix; }
		inline float getAspectRatio() const { return (float) m_screenWidth / (float) m_screenHeight; }

	private:

		int m_screenWidth = 500;
		int	m_screenHeight = 500;
		bool m_needsMatrixUpdate = true;
		float m_scale = 1.f;
		glm::vec2 m_position = glm::vec2(0.f, 0.f);
		glm::mat4 m_cameraMatrix = glm::mat4(1.f);
		glm::mat4 m_orthoMatrix = glm::mat4(1.f);
	};

}