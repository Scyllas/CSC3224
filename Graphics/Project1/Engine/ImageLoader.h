#pragma once
#include "GLTexture.h"
//#include "picoPNG.h" used by the tutorial code
#include "IOManager.h"
#include <String.h>
#include "EngineErrors.h"


#define STB_IMAGE_IMPLEMENTATION
#include "../dependencies/stb-master/stb_image.h"

namespace Engine {
	class ImageLoader
	{
	public:

	//	static GLTexture loadPNG(std::string filePath);
		static GLTexture loadPNGstbi(std::string filePath);
	};

}