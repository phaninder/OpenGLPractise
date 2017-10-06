
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std;


void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

//const char *vertexShaderSource = "#version 410 core\n"
//"layout (location=0) in vec3 aPos;\n"
//"void main()\n"
//"{\n"
//"	gl_Position=vec4(aPos.x,aPos.y,aPos.x,1.0f);\n"
//"}\0";
//
//const char *fragShaderSource = "#version 410 core\n"
//"out vec4 FragColor;\n"
//"void main()\n"
//"{\n"
//"	FragColor=vec4(1.0f,0.25f,0.35f,1.0f);\n"
//"}\n\0";

const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"out vec4 vertexColor;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"	vertexColor = vec4(aColor,1.0f);\n"
"}\0";
const char *fragShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec4 vertexColor;\n"
"uniform vec4 ourColor;\n"
"void main()\n"
"{\n"
"   FragColor =vertexColor;\n"
"}\n\0";


int DrawTriangle()
{
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwInit();
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
	
	//Compile shader
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader);

	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
		cout << "Error compiling vertex shader:" << infoLog << endl;
	}

	//Compile frag shader
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragmentShader, 1, &fragShaderSource, nullptr);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
		cout << "Error compiling fragment shader" << infoLog << endl;
	}

	//Make shader program
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
		cout << "Error linking shader program:" << infoLog << endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Create vbo and vao
	//GLfloat vertices[] = {
	//	// first triangle
	//	-0.5f,0.5f,0.0f,
	//	-0.75f,-0.5f,0.0f,
	//	-0.25f,-0.5f,0.0f,
	//	// second triangle
	//	0.5f,0.5f,0.0f,
	//	0.75f,-0.5f,0.0f,
	//	0.25f,-0.5f,0.0f
	//};

	GLfloat vertices[] = {
		// positions         // colors
		0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
		0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
	};

	unsigned int indices[] = {
		0,1,2,
		//3,4,5
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

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

	int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2f, 0.5f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		glUseProgram(shaderProgram);
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 6);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();
//	glDeleteVertexArrays(1, &VAO1);
	//glDeleteBuffers(1, &vbo1);
	//glDeleteBuffers(1, &vbo1);
	return 1;
}