#pragma once

#include <glm/glm.hpp>
#include <Engine/Vertex.h>
#include <Engine/SpriteBatch.h>

class Light {
public:
	void draw(Engine::SpriteBatch& spriteBatch) {
		glm::vec4 destRect;
		destRect.x = position.x - size / 2.f;
		destRect.y = position.y - size / 2.f;
		destRect.z = size;
		destRect.w = size;
		spriteBatch.draw(destRect, glm::vec4(-1.f, -1.f, 2.f, 2.f), 0, 0.f, color, 0.f);
	}

	Engine::ColorRGBA8 color;
	glm::vec2 position;
	float size;
};