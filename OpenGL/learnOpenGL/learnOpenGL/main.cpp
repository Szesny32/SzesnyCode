#include "include.h"
#include "userInput.h"
#include "viewport.h"

const GLchar* vertexShaderSource =
	"#version 330 core\n"
	"layout(location=0) in vec3 aPos;\n"
	"void main()\n"
	"{\n"
	"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	"}\0";

const GLchar* fragmentShaderSource =
	"#version 330 core\n"
	"out vec4 FragColor;\n"
	"void main()\n"
	"{\n"
	"	FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
	"}\0";

void  szesnyCreateShader(GLuint &shader, GLenum type, const GLchar*const*string,GLsizei count=1,const GLint*length=NULL)
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

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(1280, 720, "OpenGL", NULL, NULL);

	if (!window)
	{
		std::cerr << "Failed to create GLFWwindow " << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, resizeViewport);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to init GLAD" << std::endl;
		glfwTerminate();
		return -1;
	}

	GLuint vertexShader, fragmentShader;
	szesnyCreateShader(vertexShader, GL_VERTEX_SHADER, &vertexShaderSource);
	szesnyCreateShader(fragmentShader, GL_FRAGMENT_SHADER, &fragmentShaderSource);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	while (!glfwWindowShouldClose(window))
	{
		userInput(window);
		glClearColor(0.926f, 0.836f, 0.789f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();

	}
	glfwTerminate();
	return 0;
}
