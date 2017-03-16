#include "Camera2D.h"



namespace Bengine {
	Camera2D::Camera2D() :
		_position(0.f, 0.f),
		_cameraMatrix(1.f),
		_orthoMatrix(1.f),
		_scale(1.f),
		_needsMatrixUpdate(true),
		_screenWidth(500),
		_screenHeight(500) {



	}


	Camera2D::~Camera2D() {

	}

	void Camera2D::update() {

		if (_needsMatrixUpdate) {
			glm::vec3 translate(-_position.x + _screenWidth / 2, -_position.y + _screenHeight / 2, 0.f);
			_cameraMatrix = glm::translate(_orthoMatrix, translate);

			glm::vec3 scale(_scale, _scale, 0.f);
			_cameraMatrix = glm::scale(glm::mat4(1.f), scale) * _cameraMatrix;

			_needsMatrixUpdate = false;
		}

	}

	void Camera2D::init(int screenWidth, int screenHeight) {

		_screenWidth = screenWidth;
		_screenHeight = screenHeight;
		_orthoMatrix = glm::ortho(0.f, (float)_screenWidth, 0.f, (float)_screenHeight);
	}
	glm::vec2 Camera2D::convertScreenToWorld(glm::vec2 screenCoords) {

		//invert y
		screenCoords.y = _screenHeight - screenCoords.y;
		//world coords
		screenCoords -= glm::vec2(_screenWidth / 2, _screenHeight / 2);
		//counter the scaling
		screenCoords /= _scale;
		//translate with camera
		screenCoords += _position;

		return screenCoords;
	}

	//screen culling
	bool Camera2D::isBoxInView(const glm::vec2 & position, const glm::vec2 & dimensions) {

		glm::vec2 scaledScreenDimensions = glm::vec2(_screenWidth, _screenHeight) / (_scale);

		const float MIN_DISTANCE_X = dimensions.x / 2.f + scaledScreenDimensions.x / 2.f;
		const float MIN_DISTANCE_Y = dimensions.y / 2.f + scaledScreenDimensions.y / 2.f;

		glm::vec2 centerPos = position + dimensions / 2.f;
		glm::vec2 centerCameraPos = _position;

		glm::vec2 distVec = centerPos - centerCameraPos;

		float xDepth = MIN_DISTANCE_X - abs(distVec.x);
		float yDepth = MIN_DISTANCE_Y - abs(distVec.y);

		if (xDepth > 0 && yDepth > 0) {
			return true;
		}
		return false;

	}
}