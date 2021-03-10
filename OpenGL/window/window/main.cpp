#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include "iostream"
void resizeViewport(GLFWwindow* window, int width, int height);
void userInput(GLFWwindow* window);
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
void resizeViewport(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
void userInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
