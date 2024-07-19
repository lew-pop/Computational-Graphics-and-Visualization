#pragma once
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "Shape.h"

using namespace std;

class Shader {

public:

	// Constructor and Destructor
	Shader();
	~Shader();

	// Getters 
	GLuint getProgram() const; 

	// Setters 
	void setProgram(GLuint programId);

	// Global functions for shader program
	bool CreateShaderProgram(const char* vsFilename, const char* fsFilename);
	void use();

	void setUniform(const GLchar* name, const glm::vec3& v);
	void setUniform(const GLchar* name, const glm::mat4& m);
	void setUniform(const GLchar* name, const glm::vec2& m);
	void setUniform(const GLchar* name, const GLfloat f);
	void setUniform(const GLchar* name, const GLint v);
	void setUniformSampler(const GLchar* name, const GLint& slot);

	enum ShaderType
	{
		VERTEX,
		FRAGMENT,
		PROGRAM
	};

private:

	GLuint programId;

	string fileToString(const string& filename);
	void  checkCompileErrors(GLuint shader, ShaderType type);
};
