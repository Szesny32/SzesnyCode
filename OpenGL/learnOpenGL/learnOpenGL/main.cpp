#include "include.h"
#include "userInput.h"
#include "viewport.h"
#include "shaders.h"


const GLchar* vertexShaderSource =
"#version 330 core\n"	
"layout(location=0) in vec3 aPos;\n"	//location of the input variable; input vertex data (x,y,z)
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const GLchar* fragmentShaderSource =
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);\n" //RGBA
"}\0";

float vertexData[] = 
{
	-0.1f, -0.1f, 0.0f, 
	 0.1f, -0.1f, 0.0f, 
	 -0.1f,  0.1f, 0.0f  
};


int main()
{

	//#GLFW initialization & configuration
	glfwInit();											//version X.X
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);		//version 3.X
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);		//version 3.3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//#creatining program window (width & height in pixels, title, fullscreen mode, shared resources)
	GLFWwindow* window = glfwCreateWindow(1280, 720, "OpenGL", NULL, NULL);
	if (!window)
	{
		std::cerr << "Failed to create GLFWwindow " << std::endl;
		glfwTerminate();
		return -1;
	}
	//#setting the context (OpenGL state machine)
	glfwMakeContextCurrent(window);

	//#resize Viewport (a custom function for which there is a prototype)
	glfwSetFramebufferSizeCallback(window, resizeViewport);

	//#retrieve locations of OpenGL functions
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to init GLAD" << std::endl;
		glfwTerminate();
		return -1;
	}

	//#creating vertex & fragment shaders
	GLuint vertexShader, fragmentShader;
	szesnyCreateShader(vertexShader, GL_VERTEX_SHADER, &vertexShaderSource);
	szesnyCreateShader(fragmentShader, GL_FRAGMENT_SHADER, &fragmentShaderSource);

	//#creating shader program
	GLuint shaderProgram = szesnyCreateProgram(vertexShader, fragmentShader);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//#configure the loading of vertex data
	GLuint VBO;	//vertex buffer object can store a large number of vertices in the GPU's memory.
	
	GLuint VAO;	
	/*	! Core OpenGL requires that we use a VAO !
		vertex array object store state configuration. 
		can be bound just like a vertex buffer object and any subsequent vertex attribute calls 
		from that point on will be stored inside the VAO.
		VAO stores:
		- call to glEnableVertexAttribArray or glDisableVertexAttribArray
		- vertex attribute configurations via glVertexAttribPointer
		- VBO associated with vertex attributes by calls to glVertexAttributePointer */

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO); //To use a VAO all you have to do is bind the VAO
	glBindBuffer(GL_ARRAY_BUFFER, VBO); 
	/*	buffer type of VBO is GL_ARRAY_BUFFER
		From that point on any buffer calls we make(on the GL_ARRAY_BUFFER target) will be
		used to configure the currently bound buffer, which is VBO. */

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	/*	copies the previously defined vertex data into the buffer’s memory
	The fourth parameter specifies how we want the graphics card to manage the given data. */
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	/*	we have to specify how OpenGL should interpret the vertex data before rendering.
		The first argument specifies wich vertex attribute we want to configure
		(we specified the location of position vertex attribute in the vertex shader with layout(location=0)).
		The second argument specifies the vector size of the vertex attribute.
		The third argument specifies the type of data.
		The fourth argument specifies if we want the data to be normalized.
		The fifth argument is stride - space between consecutive vertex attributes.
		The sixth argument is offset od where the position data begins in the buffer.*/


	glEnableVertexAttribArray(0); //enable the giving the vertex attribute vertex attribute location as its argument; vertex attributes are disabled by default.


	//#unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//#render loop
	while (!glfwWindowShouldClose(window))
	{
		userInput(window);

		glClearColor(0.926f, 0.836f, 0.789f, 1.0f);//specify the color to clear the screen
		glClear(GL_COLOR_BUFFER_BIT);
		/*	We can clear the screen’s color buffer using glClear where we pass in buffer bits to specify which buffer we would like to clear.
			The possible bits we can set are GL_COLOR_BUFFER_BIT, GL_DEPTH_BUFFER_BIT and GL_STENCIL_BUFFER_BIT */

		glUseProgram(shaderProgram); 
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents(); //callback management
	}

	//#end
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);
	glfwTerminate();
	return 0;
}




