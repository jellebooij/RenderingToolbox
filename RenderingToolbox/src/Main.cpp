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

#include "math01/Vec3.h"
#include "math01/Mat4.h"

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
	window = glfwCreateWindow(1500, 1000, "Hello World", NULL, NULL);
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


	
		

		
		




	Mat4 proj = Mat4::Perspective(70.0f,1.5f,0.1f,100.0f);


	

	unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "proj");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, proj.DataPointer());



	Vec3 vec;
	vec.x = 10;
	vec.y = 10;

	Vec3 vec2;
	vec2.x = 10;

	vec2.y = 10;

	Vec4 v4(1.0f,0.0f,0.0f,0.0f);

	Vec3 v3(1,0,0);
	Vec3 v5(0,1,0);

	v3 = v3 + v5 * 10;

	

	Mat4 one(200);
	Mat4 two;

	Mat4 three = one * two;

	v4 = one * v4;

	std::cout << v3.y;




	vec.Normalize();


	



	


	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		Mat4 henk(1.0);
		Mat4 rot(1.0);
		Mat4 rot2(1.0);
		Mat4 transfomers(1.0);

		henk = Mat4::Scale(Vec3(1.0f, 1.0f, 1.0f));

		//rot = Mat4::Rotate();
		//rot2 = Mat4::Rotate();

		Quaternion q1 = Quaternion::AngleAxis(yPosition * 0.1f, Vec3(1, 0, 0));
		Quaternion q2 = Quaternion::AngleAxis(xPosition * 0.1f, Vec3(0, 1, 0));

	

		Quaternion q3 = q1.Multiply(q2);
		
		transfomers = Mat4::Translate(Vec3(0, 0, -2.5f));
		
		rot2 = Mat4::Rotate(q3);
		rot2 *= transfomers;
		
		
		henk *= rot2;

		
		GLfloat* test = henk.DataPointer();
		unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, test);



		glDrawArrays(GL_TRIANGLES,0,36);



		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}