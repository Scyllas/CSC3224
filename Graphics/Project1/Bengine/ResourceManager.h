#pragma once

#include "textureCache.h"

namespace Bengine {
	class ResourceManager
	{
	public:

		static GLTexture getTexture(std::string texturePath);


	private:
		static TextureCache m_textureCache;
	};
}
