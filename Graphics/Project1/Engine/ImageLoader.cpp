#include "ImageLoader.h"

// CSC3224 NCODE [Benjamin Bowen] [140189542] 
namespace Engine {
	
	GLTexture ImageLoader::loadPNGstbi(std::string filePath) {
	
		GLTexture texture = {};


		std::vector<unsigned char>in;
		std::vector<unsigned char>out;
	
		if (IOManager::readFileToBuffer(filePath, in) == false) {
			fatalError("Failed to load PNG file to buffer!");
		}

		int width, height, bpp;
		unsigned char* rgb = stbi_load(filePath.c_str(), &width, &height, &bpp, 3);
		// rgb is now three bytes per pixel, width*height size. Or NULL if load failed.
		// Do something with it...
		stbi_image_free(rgb);

	

		glGenTextures(1, &(texture.id));

		glBindTexture(GL_TEXTURE_2D, texture.id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(out[0]));


		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);

		texture.width = width;
		texture.height = height;
		texture.filePath = filePath;

		return texture;
	
	}
	// CSC3224	NCODE BLOCK ENDS.
	
	/* how the tutorial series did it

	GLTexture ImageLoader::loadPNG(std::string filePath) {

		GLTexture texture = {};


		std::vector<unsigned char>in;
		std::vector<unsigned char>out;
		unsigned long width, height;

		if (IOManager::readFileToBuffer(filePath, in) == false) {
			fatalError("Failed to load PNG file to buffer!");
		}

		int errorCode = decodePNG(out, width, height, &(in[0]), in.size());
		

		if (errorCode != 0) {
			fatalError("decodePNG failed with error: " + std::to_string(errorCode));
		}

		glGenTextures(1, &(texture.id));

		glBindTexture(GL_TEXTURE_2D, texture.id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(out[0]));


		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);

		texture.width = width;
		texture.height = height;
		texture.filePath = filePath;

		return texture;
	}

	*/
}