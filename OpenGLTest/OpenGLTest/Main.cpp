#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <thread>

using namespace std;
const char* vertexSource = R"glsl(
    #version 150 core

    in vec2 position;

    void main()
    {
        gl_Position = vec4(position, 0.0f, 1.0f);
    }
)glsl";

const char* fragmentSource = R"glsl(
	#version 150 core
	out vec4 outColor;
	void main()
	{
		outColor = vec4(1.0f,0.0f,0.0f,1.0f);
	}
)glsl";
int main()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow *window = glfwCreateWindow(800, 600, "OpenGL", nullptr, nullptr);

	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	glewInit();
	
	float vertices[] = {
		0.0f,0.5f,
		0.5f,-0.5f,
		-0.5f,-0.5f
	};

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	// Vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);

	glCompileShader(vertexShader);

	//check shader status
	GLint status;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);

	if (!status)
	{
		char buffer[512];
		glGetShaderInfoLog(vertexShader, 512, NULL, buffer);
		cout << "Error::Vertex shade failed\n" << buffer << endl;
	}

	//compile frag shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);

	if (!status)
	{
		char buffer[512];
		glGetShaderInfoLog(fragmentShader, 512, NULL, buffer);
		cout << "Error::Fragment shader failed\n" << buffer << endl;
	}

	//Combine both shaders
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	glBindFragDataLocation(shaderProgram, 0, "outColor");

	//link shader
	glLinkProgram(shaderProgram);

	// Check program status
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);

	if (!status)
	{
		char buffer[512];
		glGetProgramInfoLog(shaderProgram, 512, NULL, buffer);
		cout << "Error Linking program:" << buffer << endl;
	}

	GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
	
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);
	
	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindVertexArray(0);

	while (!glfwWindowShouldClose(window))
	{		
		glfwPollEvents();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		glfwSwapBuffers(window);

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
	}


	glfwTerminate();
	return 0;
}