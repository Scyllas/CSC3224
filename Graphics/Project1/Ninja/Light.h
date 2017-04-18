#pragma once

#include <glm/glm.hpp>
#include <Bengine/Vertex.h>
#include <Bengine/SpriteBatch.h>

class Light {
public:
	void draw(Bengine::SpriteBatch& spriteBatch) {
		glm::vec4 destRect;
		destRect.x = position.x - size / 2.f;
		destRect.y = position.y - size / 2.f;
		destRect.z = size;
		destRect.w = size;
		spriteBatch.draw(destRect, glm::vec4(-1.f, -1.f, 2.f, 2.f), 0, 0.f, color, 0.f);
	}

	Bengine::ColorRGBA8 color;
	glm::vec2 position;
	float size;
};