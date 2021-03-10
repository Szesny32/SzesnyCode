#ifndef SHADERS_H
#define SHADERS_H

void szesnyCreateShader(GLuint& shader, GLenum type, const GLchar* const* string, GLsizei count = 1, const GLint* length = NULL);
GLuint szesnyCreateProgram(GLuint vertexShader, GLuint fragmentShader);



#endif