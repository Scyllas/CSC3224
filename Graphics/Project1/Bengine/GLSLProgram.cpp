#include "GLSLProgram.h"
#include "Errors.h"
#include <vector>

#include <fstream>
namespace Bengine {
	GLSLProgram::GLSLProgram() :_numAttributes(0), _programID(0), _vertexShaderID(0), _fragmentShaderID(0)
	{



	}


	GLSLProgram::~GLSLProgram()
	{
	}

	void GLSLProgram::compileShaders(const std::string & vertexShaderFilePath, const std::string & fragmentShaderFilepath) {

		//shaders sucessfully compiled

		_programID = glCreateProgram();

		_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		if (_vertexShaderID == 0) {

			fatalError("Vertex shader failed to be created!");

		}
		_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		if (_fragmentShaderID == 0) {

			fatalError("Fragment shader failed to be created!");

		}

		compileShader(vertexShaderFilePath, _vertexShaderID);
		compileShader(fragmentShaderFilepath, _fragmentShaderID);

	}


	void GLSLProgram::linkShaders() {



		//attach to our program
		glAttachShader(_programID, _vertexShaderID);
		glAttachShader(_programID, _fragmentShaderID);

		//link the program
		glLinkProgram(_programID);

		GLint isLinked = 0;
		//note getprogram instead of getshader now
		glGetProgramiv(_programID, GL_LINK_STATUS, (int *)&isLinked);
		if (isLinked == GL_FALSE) {

			GLint maxLength = 0;
			glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);

			//maxlength include nullchar
			std::vector<char> errorLog(maxLength);
			glGetProgramInfoLog(_programID, maxLength, &maxLength, &errorLog[0]);


			//cleanup
			glDeleteProgram(_programID);
			glDeleteShader(_vertexShaderID);
			glDeleteShader(_fragmentShaderID);


			std::printf("%s\n", &(errorLog[0]));
			fatalError("Shaders failed to link!");

		}

		glDetachShader(_programID, _vertexShaderID);
		glDetachShader(_programID, _fragmentShaderID);
		glDeleteShader(_vertexShaderID);
		glDeleteShader(_fragmentShaderID);

	}

	void GLSLProgram::addAttribute(const std::string & attributeName)
	{

		glBindAttribLocation(_programID, _numAttributes++, attributeName.c_str());

	}

	GLint GLSLProgram::getUniformLocation(const std::string & uniformName) {

		GLint location = glGetUniformLocation(_programID, uniformName.c_str());

		if (location == GL_INVALID_INDEX) {

			fatalError("Uniform " + uniformName + " not found in shader!");


		}
		return location;
	}

	void GLSLProgram::use() {

		glUseProgram(_programID);
		for (int i = 0; i < _numAttributes; i++) {
			glEnableVertexAttribArray(i);
		}
	}

	void GLSLProgram::unuse() {

		glUseProgram(0);
		for (int i = 0; i < _numAttributes; i++) {
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