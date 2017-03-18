#pragma once

#include <string>
#include <GL/glew.h>
namespace Bengine {
	class GLSLProgram
	{
	public:
		GLSLProgram();
		~GLSLProgram();

		void compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilepath);

		void linkShaders();

		void addAttribute(const std::string& attributeName);

		GLint getUniformLocation(const std::string& uniformName);

		void use();
		void unuse();

	private:
		int m_numAttributes;

		void compileShader(const std::string& filepath, GLuint id);

		GLuint m_programID;
		GLuint m_vertexShaderID;
		GLuint m_fragmentShaderID;
	};

}