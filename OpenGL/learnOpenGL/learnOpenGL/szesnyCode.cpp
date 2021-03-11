#include "include.h"
#include "szesnyCode.h"
#include "shaders.h"
#include "userInput.h"

void F1_Window(GLFWwindow* window)
{

	while (!glfwWindowShouldClose(window))
	{
		userInput(window);
		glClearColor(0.926f, 0.836f, 0.789f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}
void F2_Triangle(GLFWwindow* window)
{

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
		0.0f, 0.5f, 0.0f
	};

	GLuint vertexShader, fragmentShader;
	szesnyCreateShader(vertexShader, GL_VERTEX_SHADER, &vertexShaderSource);
	szesnyCreateShader(fragmentShader, GL_FRAGMENT_SHADER, &fragmentShaderSource);

	GLuint shaderProgram = szesnyCreateProgram(vertexShader, fragmentShader);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	GLuint VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);
	glUseProgram(shaderProgram);
	while (!glfwWindowShouldClose(window))
	{
		userInput(window);
		glClearColor(0.926f, 0.836f, 0.789f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//glBindVertexArray(VAO);
		//glUseProgram(shaderProgram);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteProgram(shaderProgram);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &VAO);
}


void F3_Rectangle_EBO(GLFWwindow* window)
{

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
		0.5f, 0.5f, 0.0f, 
		0.5f, -0.5f, 0.0f, 
		-0.5f, -0.5f, 0.0f, 
		-0.5f, 0.5f, 0.0f 

	};
	unsigned int indices[] = 
	{ 
		0, 1, 3, 
		1, 2, 3 
	};

	GLuint vertexShader, fragmentShader;
	szesnyCreateShader(vertexShader, GL_VERTEX_SHADER, &vertexShaderSource);
	szesnyCreateShader(fragmentShader, GL_FRAGMENT_SHADER, &fragmentShaderSource);

	GLuint shaderProgram = szesnyCreateProgram(vertexShader, fragmentShader);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	GLuint VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);
	glUseProgram(shaderProgram);
	while (!glfwWindowShouldClose(window))
	{
		userInput(window);
		glClearColor(0.926f, 0.836f, 0.789f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//glUseProgram(shaderProgram);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteProgram(shaderProgram);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &VAO);
	glDeleteBuffers(1, &EBO);
}



void F3_Rectangle_ex1(GLFWwindow* window)
{

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
		0.5f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f
	};
	

	GLuint vertexShader, fragmentShader;
	szesnyCreateShader(vertexShader, GL_VERTEX_SHADER, &vertexShaderSource);
	szesnyCreateShader(fragmentShader, GL_FRAGMENT_SHADER, &fragmentShaderSource);

	GLuint shaderProgram = szesnyCreateProgram(vertexShader, fragmentShader);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	GLuint VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);
	glUseProgram(shaderProgram);
	while (!glfwWindowShouldClose(window))
	{
		userInput(window);
		glClearColor(0.926f, 0.836f, 0.789f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//glUseProgram(shaderProgram);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteProgram(shaderProgram);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &VAO);
}

void F3_Rectangle_ex2(GLFWwindow* window)
{

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
		0.5f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,
	};
	float vertexData2[]=
	{
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f
	};


	GLuint vertexShader, fragmentShader;
	szesnyCreateShader(vertexShader, GL_VERTEX_SHADER, &vertexShaderSource);
	szesnyCreateShader(fragmentShader, GL_FRAGMENT_SHADER, &fragmentShaderSource);

	GLuint shaderProgram = szesnyCreateProgram(vertexShader, fragmentShader);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	GLuint VAO[2], VBO[2];
	glGenVertexArrays(2, VAO);
	glGenBuffers(2, VBO);

	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData2), vertexData2, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glUseProgram(shaderProgram);
	while (!glfwWindowShouldClose(window))
	{
		userInput(window);
		glClearColor(0.926f, 0.836f, 0.789f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glBindVertexArray(VAO[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteProgram(shaderProgram);
	glDeleteBuffers(2, VBO);
	glDeleteBuffers(2, VAO);
}

void F3_Rectangle_ex3(GLFWwindow* window)
{

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
		"	FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n" //RGBA
		"}\0";

	const GLchar* fragmentShaderSource2 =
		"#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"	FragColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);\n" //RGBA
		"}\0";

	float vertexData[] =
	{
		0.5f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,
	};
	float vertexData2[] =
	{
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f
	};





	GLuint vertexShader, fragmentShader, fragmentShader2;
	szesnyCreateShader(vertexShader, GL_VERTEX_SHADER, &vertexShaderSource);
	szesnyCreateShader(fragmentShader, GL_FRAGMENT_SHADER, &fragmentShaderSource);
	szesnyCreateShader(fragmentShader2, GL_FRAGMENT_SHADER, &fragmentShaderSource2);
	GLuint shaderProgram = szesnyCreateProgram(vertexShader, fragmentShader);
	GLuint shaderProgram2 = szesnyCreateProgram(vertexShader, fragmentShader2);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteShader(fragmentShader2);

	GLuint VAO[2], VBO[2];
	glGenVertexArrays(2, VAO);
	glGenBuffers(2, VBO);

	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData2), vertexData2, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	while (!glfwWindowShouldClose(window))
	{
		userInput(window);
		glClearColor(0.926f, 0.836f, 0.789f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glUseProgram(shaderProgram2);
		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteProgram(shaderProgram);
	glDeleteProgram(shaderProgram2);
	glDeleteBuffers(2, VBO);
	glDeleteBuffers(2, VAO);
}





void F_RoseOfTheWind(GLFWwindow*window)
{

	const GLchar* vertexShaderSource =
		"#version 330 core\n"
		"layout(location=0) in vec3 aPos;\n"	//location of the input variable; input vertex data (x,y,z)
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


	GLuint vertexShader, fragmentShader, fragmentShader2;
	szesnyCreateShader(vertexShader, GL_VERTEX_SHADER, &vertexShaderSource);
	szesnyCreateShader(fragmentShader, GL_FRAGMENT_SHADER, &fragmentShaderSource);
	GLuint shaderProgram = szesnyCreateProgram(vertexShader, fragmentShader);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	GLuint VBO;
	GLuint VAO;
	GLuint EBO;
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
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);

	

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);



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
				glUniform4f(vertexColorLocation, Value, Value/2, 0.0f, 1.0f);
		
			glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}



	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);

}
