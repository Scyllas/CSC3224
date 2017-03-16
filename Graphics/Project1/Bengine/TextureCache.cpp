#include "TextureCache.h"
#include "ImageLoader.h"
#include <iostream>
namespace Bengine {
	TextureCache::TextureCache()
	{
	}


	TextureCache::~TextureCache()
	{
	}

	GLTexture TextureCache::getTexture(std::string texturePath) {

		//texture lookup
		auto mit = _textureMap.find(texturePath);

		if (mit == _textureMap.end()) {
			GLTexture newTexture = ImageLoader::loadPNG(texturePath);

			_textureMap.insert(make_pair(texturePath, newTexture));

			return newTexture;
		}
		return mit->second;
	}
}