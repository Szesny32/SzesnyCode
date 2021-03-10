#include "include.h"
#include "userInput.h"
#include "viewport.h"
#include "shaders.h"


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
"	FragColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);\n"
"}\0";

float vertexData[] = 
{
	-0.5f, -0.5f, 0.0f, 
	 0.5f, -0.5f, 0.0f, 
	 0.0f,  0.5f, 0.0f  
};


int main()
{

	//GLFW initialization & configuration
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Creatining program window and context
	GLFWwindow* window = glfwCreateWindow(1280, 720, "OpenGL", NULL, NULL);
	if (!window)
	{
		std::cerr << "Failed to create GLFWwindow " << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	//Resize Viewport
	glfwSetFramebufferSizeCallback(window, resizeViewport);

	//Retrieve locations of OpenGL functions
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to init GLAD" << std::endl;
		glfwTerminate();
		return -1;
	}

	//Creating vertex & fragment shaders
	GLuint vertexShader, fragmentShader;
	szesnyCreateShader(vertexShader, GL_VERTEX_SHADER, &vertexShaderSource);
	szesnyCreateShader(fragmentShader, GL_FRAGMENT_SHADER, &fragmentShaderSource);

	//Creating shader program
	GLuint shaderProgram = szesnyCreateProgram(vertexShader, fragmentShader);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//Configure the loading of vertex data
	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData,GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//Unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//Render loop
	while (!glfwWindowShouldClose(window))
	{
		userInput(window);

		glClearColor(0.926f, 0.836f, 0.789f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram); 
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//End
	glDeleteProgram(shaderProgram);
	glfwTerminate();
	return 0;
}




