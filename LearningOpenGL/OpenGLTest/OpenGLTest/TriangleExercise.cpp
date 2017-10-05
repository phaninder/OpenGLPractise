
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std;


void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

int DrawTriangle()
{
	glfwInit();
	glfwWindowHint(GLFW_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_VERSION_MINOR, 3);

	GLFWwindow *window = glfwCreateWindow(800, 600, "Triangle", nullptr, nullptr);

	if (window == nullptr)
	{
		cout << "Error::Failed to initialise Window" << endl;
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialise GLAD" << endl;
		return -1;
	}

	// Create vbo and vao
	GLfloat vertices[] = {
		// first triangle
		-0.5f,0.5f,0.0f,
		-0.75f,-0.5f,0.0f,
		-0.25f,-0.5f,0.0f,
		// second triangle
		0.5f,0.5f,0.0f,
		0.75f,-0.5f,0.0f,
		0.25f,-0.5f,0.0f
	};

	unsigned int indices[] = {
		0,1,2,
		3,4,5
	};

/*
	GLfloat vertices2[] = {
		0.5f,0.5f,0.0f,
		0.75f,-0.5f,0.0f,
		0.25f,-0.5f,0.0f
	};*/

	//Create buffer and store data
	unsigned int vbo, VAO,EBO;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	//Create vertex array obj and store vbo
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	/*unsigned int vbo1, VAO1;
	glGenVertexArrays(1, &VAO1);
	glBindVertexArray(VAO1);
	glGenBuffers(1, &vbo1);
	glBindBuffer(GL_ARRAY_BUFFER, vbo1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

	//Create vertex array obj and store vbo
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	*/
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2f, 0.5f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 6);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &EBO);

//	glDeleteVertexArrays(1, &VAO1);
	//glDeleteBuffers(1, &vbo1);
	//glDeleteBuffers(1, &vbo1);
	return 1;
}