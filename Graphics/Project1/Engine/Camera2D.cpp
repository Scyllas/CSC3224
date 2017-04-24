#include "Camera2D.h"



namespace Engine {
	Camera2D::Camera2D() {

	}


	Camera2D::~Camera2D() {

	}

	void Camera2D::update() {

		if (m_needsMatrixUpdate) {
			glm::vec3 translate(-m_position.x + m_screenWidth / 2, -m_position.y + m_screenHeight / 2, 0.f);
			m_cameraMatrix = glm::translate(m_orthoMatrix, translate);

			glm::vec3 scale(m_scale, m_scale, 0.f);
			m_cameraMatrix = glm::scale(glm::mat4(1.f), scale) * m_cameraMatrix;

			m_needsMatrixUpdate = false;
		}

	}

	void Camera2D::init(int screenWidth, int screenHeight) {

		m_screenWidth = screenWidth;
		m_screenHeight = screenHeight;
		m_orthoMatrix = glm::ortho(0.f, (float)m_screenWidth, 0.f, (float)m_screenHeight);
	}
	glm::vec2 Camera2D::convertScreenToWorld(glm::vec2 screenCoords) {

		//invert y
		screenCoords.y = m_screenHeight - screenCoords.y;
		//world coords
		screenCoords -= glm::vec2(m_screenWidth / 2, m_screenHeight / 2);
		//counter the scaling
		screenCoords /= m_scale;
		//translate with camera
		screenCoords += m_position;

		return screenCoords;
	}

	//screen culling
	bool Camera2D::isBoxInView(const glm::vec2 & position, const glm::vec2 & dimensions) {

		glm::vec2 scaledScreenDimensions = glm::vec2(m_screenWidth, m_screenHeight) / (m_scale);

		const float MIN_DISTANCE_X = dimensions.x / 2.f + scaledScreenDimensions.x / 2.f;
		const float MIN_DISTANCE_Y = dimensions.y / 2.f + scaledScreenDimensions.y / 2.f;

		glm::vec2 centerPos = position + dimensions / 2.f;
		glm::vec2 centerCameraPos = m_position;

		glm::vec2 distVec = centerPos - centerCameraPos;

		float xDepth = MIN_DISTANCE_X - abs(distVec.x);
		float yDepth = MIN_DISTANCE_Y - abs(distVec.y);

		if (xDepth > 0 && yDepth > 0) {
			return true;
		}
		return false;

	}
}