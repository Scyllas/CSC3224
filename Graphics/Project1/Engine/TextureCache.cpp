#include "TextureCache.h"
#include "ImageLoader.h"
#include <iostream>
// CSC3224 NCODE [Benjamin Bowen] [140189542] 
namespace Engine {
	TextureCache::TextureCache()
	{
	}


	TextureCache::~TextureCache()
	{
	}

	GLTexture TextureCache::getTexture(std::string texturePath) {

		//texture lookup
		auto mit = m_textureMap.find(texturePath);

		if (mit == m_textureMap.end()) {
			GLTexture newTexture = ImageLoader::loadPNGstbi(texturePath);

			m_textureMap.insert(make_pair((std::string)texturePath, newTexture));

			return newTexture;
		}
		return mit->second;
	}
}

// CSC3224	NCODE BLOCK ENDS.