#include "include.h"
#include "shaders.h"
void szesnyCreateShader(GLuint& shader, GLenum type, const GLchar* const* string, GLsizei count , const GLint* length )
{
	shader = glCreateShader(type);
	glShaderSource(shader, count, string, length);
	glCompileShader(shader);
	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[512];
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cerr << "Shader ID: " << shader << " Type: ";
		switch (type)
		{
		case GL_VERTEX_SHADER:
			std::cout << "vertex shader" << std::endl;
			break;
		case GL_FRAGMENT_SHADER:
			std::cout << "fragment shader" << std::endl;
			break;
		default:
			std::cout << type << std::endl;
		}
		std::cerr << "Compilation failed: " << infoLog << std::endl;
	}
}

GLuint szesnyCreateProgram(GLuint vertexShader, GLuint fragmentShader)
{
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	GLint success;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[512];
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cerr << "Shader Program ID: " << shaderProgram << std::endl;
		std::cerr << "Linking failed: " << infoLog << std::endl;
	}
	return shaderProgram;
}
