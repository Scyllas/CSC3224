#pragma once

#include <vector>
namespace Engine {
	extern int decodePNG(std::vector<unsigned char>& outm_image, 
		unsigned long& imagem_width, 
		unsigned long& imagem_height, 
		const unsigned char* inm_png, 
		size_t inm_size, 
		bool convertm_tom_rgba32 = true);
}