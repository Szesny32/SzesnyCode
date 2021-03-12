#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>


void viewportResize(GLFWwindow* window, int width, int height);
void userInput(GLFWwindow* window);

GLuint createShader();
void linkVertexAttributes(GLuint &VBO, GLuint &VAO, GLuint &EBO);


const GLchar* vertexShaderSource =
"#version 330 core\n"
"layout(location=0) in vec3 aPos;\n"	
"layout(location=1) in vec3 aColor;\n"
"out vec3 ourColor;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos, 1.0);\n"
"ourColor = aColor;\n"
"}\0";

const GLchar* fragmentShaderSource =
"#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 ourColor;\n"
"uniform vec4 ourColor2;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(ourColor, 1.0f)+ourColor2;\n" //RGBA
"}\0";

float vertexData[] =
{
	0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
	0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
	0.1f, 0.1f, 0.1f, 1.0f, 0.0f, 0.0f,
	0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	0.1f, -0.1f, 0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
	-0.1f, -0.1f, 0.0f, 1.0f, 0.0f, 0.0f,
	-0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	-0.1f, 0.1f, 0.0f, 1.0f, 0.0f, 0.0f,
};
unsigned int indices[] =
{
	0,2,3,
	0,4,5,
	0,6,7,
	0,1,8,
	0,1,2,
	0,3,4,
	0,5,6,
	0,7,8
};
int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(600, 600, "OpenGL", NULL, NULL);
	if (!window)
	{
		std::cerr << "glfwCreateWindow failed" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, viewportResize);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) failed" << std::endl;
		glfwTerminate();
		return -1;
	}

	GLuint shaderProgram = createShader();

	GLuint VAO, VBO, EBO;
	linkVertexAttributes(VBO,VAO,EBO);

	GLfloat timeValue;
	GLfloat Value;
	GLint vertexColorLocation;
	glBindVertexArray(VAO);
	glUseProgram(shaderProgram);
	while (!glfwWindowShouldClose(window))
	{
		userInput(window);

		glClearColor(0.926f, 0.836f, 0.789f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		timeValue = glfwGetTime();
		Value = sin(timeValue) / 2.0f + 0.5f;
		vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor2");
		glUniform4f(vertexColorLocation, Value, Value / 2, 0.0f, 1.0f);

		glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);
	glfwTerminate();
	return 0;

}

void viewportResize(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void userInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

GLuint createShader()
{
	GLint success;
	GLchar infoLog[512];

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cerr << "vertex shader compilation failed\n" << infoLog << std::endl;
	}

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cerr << "fragment shader compilation failed\n" << infoLog << std::endl;
	}

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cerr << "program shader linking failed\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	return shaderProgram;
}
void linkVertexAttributes(GLuint &VBO,GLuint& VAO,GLuint &EBO)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}