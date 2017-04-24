#pragma once

#include <GL\glew.h>
#include "GLTexture.h"
#include "ResourceManager.h"
namespace Engine {
	class Sprite
	{
	public:
		Sprite();
		~Sprite();

		void init(float x, float y, float width, float height, char* texturePath);

		void draw();

	private:

		float m_x;
		float m_y;
		float m_width;
		float m_height;
		GLuint m_vboID = 0;

		GLTexture m_texture;
	};
}