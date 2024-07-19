#include "Shader.h"

// Constructor
Shader::Shader(){
	programId = 0;
}

// Destructor
Shader::~Shader() {
	glDeleteProgram(programId);
}

// Getters
GLuint Shader::getProgram() const { return programId; }

// Setters
void Shader::setProgram(GLuint programId) {
	this->programId = programId;
}

void Shader::use() {
	if (programId > 0)
		glUseProgram(programId);
	else
		cout << "programId = 0!" << endl;

}

// Loads vertex and fragment shaders
bool Shader::CreateShaderProgram(const char* vsFilename, const char* fsFilename) {
	
	string vsString = fileToString(vsFilename);
	string fsString = fileToString(fsFilename);
	const GLchar* vsSourcePtr = vsString.c_str();
	const GLchar* fsSourcePtr = fsString.c_str();

	// Create the vertex and fragment shader objects
	GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

	// Retrive the shader source
	glShaderSource(vertexShaderId, 1, &vsSourcePtr, NULL);
	glShaderSource(fragmentShaderId, 1, &fsSourcePtr, NULL);

	// Compile the vertex shader
	glCompileShader(vertexShaderId);
	checkCompileErrors(vertexShaderId, VERTEX);

	glCompileShader(fragmentShaderId);
	checkCompileErrors(fragmentShaderId, FRAGMENT);	

	programId = glCreateProgram();
	if (programId == 0)
	{
		cout << "Unable to create shader program!" << endl;
		return false;
	}
	// Attach compiled shaders to the shader program
	glAttachShader(programId, vertexShaderId);
	glAttachShader(programId, fragmentShaderId);

	// Link the shader program
	glLinkProgram(programId);
	checkCompileErrors(programId, PROGRAM);

	glDeleteShader(vertexShaderId);
	glDeleteShader(fragmentShaderId);
	
	return true;
}

void  Shader::checkCompileErrors(GLuint shader, ShaderType type) {
	int success = 0;

	if (type == PROGRAM)
	{
		// Check for shader linking errors
		glGetProgramiv(programId, GL_LINK_STATUS, &success);
		if (!success)
		{
			GLint length = 0;
			glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &length);

			string infoLog(length, ' ');
			glGetProgramInfoLog(programId, length, &length, &infoLog[0]);
			cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << endl;
		}
	}
	else
	{
		// Check for shader compile errors
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			GLint length = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
			string infoLog(length, ' ');
			glGetShaderInfoLog(shader, length, &length, &infoLog[0]);
			cout << "ERROR::SHADER::" << shader << "::COMPILATION_FAILED\n" << infoLog << endl;
		}
	}
}

string Shader::fileToString(const string& filename)
{
	std::stringstream ss;
	std::ifstream file;

	// Enable ifstream object exceptions
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		file.open(filename, std::ios::in);

		if (!file.fail())
		{
			// Using a std::stringstream is easier than looping through each line of the file
			ss << file.rdbuf();
		}

		file.close();
	}
	catch (std::exception ex)
	{
		std::cerr << "Error reading shader file " << filename << std::endl;
	}

	return ss.str();
}
void Shader::setUniform(const GLchar* name, const GLint v)
{
	GLint loc = glGetUniformLocation(programId, name);
	glUniform1i(loc, v);

}

void Shader::setUniform(const GLchar* name, const GLfloat f)
{
	GLint loc = glGetUniformLocation(programId, name);
	glUniform1f(loc, f);

}

void Shader::setUniform(const GLchar* name, const glm::vec2& v)
{
	GLint loc = glGetUniformLocation(programId, name);
	glUniform2f(loc, v.x, v.y);

}

void Shader::setUniform(const GLchar* name, const glm::vec3& v)
{
	GLint location = glGetUniformLocation(programId, name);
	glUniform3f(location, v.x, v.y, v.z);

}

void Shader::setUniform(const GLchar* name, const glm::mat4& m)
{
	GLint location = glGetUniformLocation(programId, name);
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(m));
	
}
void Shader::setUniformSampler(const GLchar* name, const GLint& slot) {
	glActiveTexture(GL_TEXTURE0 + slot);
	GLint location = glGetUniformLocation(programId, name);
	glUniform1i(location, slot);

}
