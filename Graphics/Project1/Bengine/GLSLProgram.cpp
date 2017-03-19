#include "GLSLProgram.h"
#include "BengineErrors.h"
#include <vector>

#include <fstream>
namespace Bengine {
	GLSLProgram::GLSLProgram() : 
		m_numAttributes(0), 
		m_programID(0), 
		m_vertexShaderID(0), 
		m_fragmentShaderID(0) {



	}


	GLSLProgram::~GLSLProgram()
	{
	}

	void GLSLProgram::compileShaders(const std::string & vertexShaderFilePath, const std::string & fragmentShaderFilepath) {

		//shaders sucessfully compiled

		m_programID = glCreateProgram();

		m_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		if (m_vertexShaderID == 0) {

			fatalError("Vertex shader failed to be created!");

		}
		m_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		if (m_fragmentShaderID == 0) {

			fatalError("Fragment shader failed to be created!");

		}

		compileShader(vertexShaderFilePath, m_vertexShaderID);
		compileShader(fragmentShaderFilepath, m_fragmentShaderID);

	}


	void GLSLProgram::linkShaders() {



		//attach to our program
		glAttachShader(m_programID, m_vertexShaderID);
		glAttachShader(m_programID, m_fragmentShaderID);

		//link the program
		glLinkProgram(m_programID);

		GLint isLinked = 0;
		//note getprogram instead of getshader now
		glGetProgramiv(m_programID, GL_LINK_STATUS, (int *)&isLinked);
		if (isLinked == GL_FALSE) {

			GLint maxLength = 0;
			glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &maxLength);

			//maxlength include nullchar
			std::vector<char> errorLog(maxLength);
			glGetProgramInfoLog(m_programID, maxLength, &maxLength, &errorLog[0]);


			//cleanup
			glDeleteProgram(m_programID);
			glDeleteShader(m_vertexShaderID);
			glDeleteShader(m_fragmentShaderID);


			std::printf("%s\n", &(errorLog[0]));
			fatalError("Shaders failed to link!");

		}

		glDetachShader(m_programID, m_vertexShaderID);
		glDetachShader(m_programID, m_fragmentShaderID);
		glDeleteShader(m_vertexShaderID);
		glDeleteShader(m_fragmentShaderID);

	}

	void GLSLProgram::addAttribute(const std::string & attributeName)
	{

		glBindAttribLocation(m_programID, m_numAttributes++, attributeName.c_str());

	}

	GLint GLSLProgram::getUniformLocation(const std::string & uniformName) {

		GLint location = glGetUniformLocation(m_programID, uniformName.c_str());

		if (location == GL_INVALID_INDEX) {

			fatalError("Uniform " + uniformName + " not found in shader!");


		}
		return location;
	}

	void GLSLProgram::use() {

		glUseProgram(m_programID);
		for (int i = 0; i < m_numAttributes; i++) {
			glEnableVertexAttribArray(i);
		}
	}

	void GLSLProgram::unuse() {

		glUseProgram(0);
		for (int i = 0; i < m_numAttributes; i++) {
			glDisableVertexAttribArray(i);
		}
	}



	void GLSLProgram::compileShader(const std::string & filepath, GLuint id)
	{

		std::ifstream vertexFile(filepath);
		if (vertexFile.fail()) {

			perror(filepath.c_str());
			fatalError("Failed to open " + filepath);

		}

		std::string fileContents = "";
		std::string line;

		while (std::getline(vertexFile, line)) {

			fileContents += line + "\n";

		}

		vertexFile.close();

		const char* contentsPtr = fileContents.c_str();
		glShaderSource(id, 1, &contentsPtr, nullptr);

		glCompileShader(id);

		GLint success = 0;
		glGetShaderiv(id, GL_COMPILE_STATUS, &success);

		if (success == GL_FALSE) {

			GLint maxLength = 0;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

			//maxlength include nullchar
			std::vector<char> errorLog(maxLength);
			glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

			//exit with failure
			glDeleteShader(id); //remove leak

			std::printf("%s\n", &(errorLog[0]));
			fatalError("Shader " + filepath + " failed to compile");

			return;

		}

	}
}