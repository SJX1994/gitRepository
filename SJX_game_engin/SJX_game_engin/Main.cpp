#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

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

	// triangle
	float  sq3;
	sq3 = float(sqrt(3));
	//顶点位置
	GLfloat vertices[] =
	{
			-0.5f,-0.5f *sq3/3 , 0.0f,

			0.5f,-0.5f *sq3/3 , 0.0f,

			0.0f,0.5f *sq3*2 / 3 , 0.0f,

			-0.5/2, 0.5*sq3/6 , 0.0f,
			0.5 / 2, 0.5*sq3 / 6 , 0.0f,
			0.0 , -0.5*sq3 / 3 , 0.0f
	};
	//顶点绘制顺序
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


	Shader shaderProgram("default.vert","default.frag");
	
	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices,sizeof(indices)); //68147

	VAO1.LinkVBO(VBO1, 0);
	VAO1.UnBind();
	VBO1.UnBind();
	EBO1.UnBind();



	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.0, 0.5, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		shaderProgram.Activate();
		VAO1.Bind();
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();

	glfwDestroyWindow(window);

	glfwTerminate();

	return 0;
}