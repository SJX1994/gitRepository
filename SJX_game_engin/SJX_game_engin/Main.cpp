#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

//const char* vertexShaderSource =
//"#version 330 core \n "
//"layout (location = 0) in vec3 aPos; \n"
//"void main() \n"
//"{ \n"
//"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0); \n"
//"} \0"
//;
//
//const char* fragmentShaderSource =
//"#version 330 core \n "
//"layout (location = 0) \n"
//"out vec4 FragColor; \n"
//"void main() \n"
//"{ \n"
//"FragColor = vec4(0.3, 0.3, 0.0, 1.0); \n"
//"}\n \0"
//;


int main() 
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// tirangle
	float  sq3;
	sq3 = float(sqrt(3));
	//����λ��
	GLfloat vertices[] =
	{
			-0.5f,-0.5f *sq3/3 , 0.0f,

			0.5f,-0.5f *sq3/3 , 0.0f,

			0.0f,0.5f *sq3*2 / 3 , 0.0f,

			-0.5/2, 0.5*sq3/6 , 0.0f,
			0.5 / 2, 0.5*sq3 / 6 , 0.0f,
			0.0 , -0.5*sq3 / 3 , 0.0f
	};
	//�������˳��
	GLuint indices[] = 
	{
			0, 3, 5,
			3, 2, 4,
			5, 4, 1
	};

	GLFWwindow* window = glfwCreateWindow(800,800,"GameEnginSJX",NULL,NULL);

	if (window == NULL)
	{
		std::cout << "failed to creat GLFW window _sjx" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);


	gladLoadGL();



	glViewport(0, 0, 800, 800);


	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram,vertexShader);
	glAttachShader(shaderProgram,fragmentShader);
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	//Vertex and Buffer s' arrary
	GLuint VAO, VBO, EBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1,&VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);


	glVertexAttribPointer(
	0,
	3,
	GL_FLOAT,
	GL_FALSE,
	3 * sizeof(float),
	(void*)0
	);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindVertexArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	/*glClearColor(0.0,0.1,0.0,1.0);

	glClear(GL_COLOR_BUFFER_BIT);

	glfwSwapBuffers(window);*/

	//show
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.0, 0.5, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glDeleteVertexArrays(1,&VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);

	glfwDestroyWindow(window);

	glfwTerminate();

	return 0;
}