#include "include.h"
#include "userInput.h"
#include "viewport.h"
#include "shaders.h"
#include "szesnyCode.h"



int main()
{

	
	glfwInit();											
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);		
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);		
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(500, 500, "OpenGL", NULL, NULL);
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


	//F1_Window(window);
	//F2_Triangle(window);
	//F3_Rectangle_EBO(window);
	//F3_Rectangle_ex1(window);
	//F3_Rectangle_ex2(window);
	//F3_Rectangle_ex3(window);
	//F_RoseOfTheWind(window);



	glfwTerminate();
	return 0;
}




