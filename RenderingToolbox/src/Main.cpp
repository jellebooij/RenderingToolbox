#include <iostream>
#include <stdio.h>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <GL/glew.h>  
#include <GLFW/glfw3.h> 
#include "Shader.h"
#include "stb_image.h"
#include "customMath.h"

float r = 0;

float xPosition = 0;
float yPosition = 0;

float prevX;
float prevY;

float x = 0;
float y = 0; 

bool mousePressed = false;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	
	glViewport(0, 0, width, height);

}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	r += yoffset * 4;
}

static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (mousePressed) {
		xPosition += (xpos - prevX);
		yPosition += (ypos - prevY);

		std::cout << (xpos - prevX) << std::endl;

		prevX = xpos;
		prevY = ypos;
	}
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	double xpos, ypos;

	glfwGetCursorPos(window, &xpos, &ypos);

	if (action == GLFW_PRESS && mousePressed == false) {
		mousePressed = true;
		prevX = xpos;
		prevY = ypos;
	}
	if(action == GLFW_RELEASE) {
		mousePressed = false;
	}

	
}


int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetCursorPosCallback(window, cursor_pos_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);


	glewInit();

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glEnable(GL_DEPTH_TEST);


	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	unsigned int indices[] = { 
		0, 1, 3, 
		1, 2, 3 
	};

	Shader ourShader("res/shaders/test.shader");

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);


	unsigned int vbo;
	glCreateBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	unsigned int ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices),indices, GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);




	int width, height, nrChannels;
	unsigned char *data = stbi_load("res/textures/container.jpg", &width, &height, &nrChannels, 0);

	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);	
	
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);


	
		

		
		




	mat4 proj;
	//proj.orthoProj(0, 640.0f, 0, 480.0f, 0.0f, 1000.0f);
	proj.perspectiveProjection(100.0f, 0.1f, 70.0f, 64.0f / 48.0f);


	

	unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "proj");
	glUniformMatrix4fv(transformLoc, 1, GL_TRUE, proj.dataPointer());



	



	


	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		mat4 henk;	
		mat4 rot;
		mat4 rot2;
		mat4 transfomers;


		transfomers.translateMatrix(0, 0,0);

		rot2.rotateMatrixAngleAxis(1, 0, 0, -yPosition * 0.1f);
		
		rot.rotateMatrixAngleAxis(0,1,0, xPosition * 0.1f);
		
		rot *= rot2;

		rot.translateMatrix(0, 0, -2.5f);

		//transfomers *= rot;

		henk = rot;




		

		

		
	
		
		GLfloat* test = henk.dataPointer();
		unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_TRUE, test);



		glDrawArrays(GL_TRIANGLES,0,36);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}