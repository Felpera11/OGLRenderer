#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"



int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 640, "Renderer", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glewInit();

	glfwSwapInterval(1);

	float positions[] = {
		-0.5, -0.5,	0.0, 0.0,	//0
		 0.5, -0.5,	1.0, 0.0,	//1
		 0.5,  0.5,	1.0, 1.0,	//2
		-0.5,  0.5,	0.0, 1.0	//3
	};

	unsigned int vertices[] = {
		0, 1, 2, //first triangle
		2, 3, 0 //second triangle
	};

	//creating the vertex array object
	unsigned int vao;
	

	VertexArray va;
	VertexBuffer vb(positions, 4 * 4 * sizeof(float));
	VertexBufferLayout layout;
	layout.Push<float>(2);
	layout.Push<float>(2);
	va.AddBuffer(vb, layout);
	
	IndexBuffer ib(vertices, 6);

	//ShaderProgramSource source = ParseShader("res/shaders/Basic.shader");
	Shader shader("res/shaders/Basic.shader");
	shader.Bind();
	/*
	bool rise = true;
	float speed = 0.004;
	int n = 0;
	int x = 125;*/
	Texture tex("res/textures/hmm.png");
	tex.Bind();


	shader.SetUniform1i("u_Texture", 0);
	shader.SetUniform4f("u_Color", 1.0, 1.0, 1.0, 1.0);

	Renderer renderer;


	float n = 1;
	float increment = -0.03f;

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		//shader.SetUniform4f("u_Color", n, n, 0.0f, 1.0f);

		n += increment;
		if (n < 0 || n > 1)
			increment = -increment;

		positions[8] += 0.003;
		positions[9] += 0.003;
		positions[12] -= 0.003;
		positions[13] += 0.003;
		VertexBuffer vb(positions, 4 * 4 * sizeof(float));
		va.AddBuffer(vb, layout);

		//shader.SetUniform4f("u_Color", n, 1 - n, 1, 1.0);
		//glDrawArrays(GL_TRIANGLES, 0, 6); //actual draw call
		renderer.Draw(va, ib, shader);

		/*if (n < x && rise)
		{
			MoveX(speed, positions);
			n++;
		}
		else
		{
			rise = false;
			MoveX(-speed, positions);
			n--;
		}
		if (n < -x)
		{
			rise = true;
		}
		//glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_DYNAMIC_DRAW);//supplies data to the buffer for openGl to draw

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}



