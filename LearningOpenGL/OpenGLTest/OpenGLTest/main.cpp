//#include <iostream>
//
//#include <GL\glew.h>
//#include <GLFW\glfw3.h>
//
//using namespace std;
//
//const GLint Width = 800, Height = 600;
//
//int newWindow()
//{
//	glfwInit();
//	cout << "GLFW initialised" << endl;
//	glfwWindowHint(GLFW_VERSION_MAJOR, 4);
//	glfwWindowHint(GLFW_VERSION_MINOR, 1);
//	/*glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);*/
//
//	GLFWwindow *window;
//	window = glfwCreateWindow(Width, Height, "Learning OpenGL", nullptr, nullptr);
//	if (nullptr == window)
//	{
//		cout << "Window is null" << endl;
//		return EXIT_FAILURE;
//	}
//
//	int screenWidth, screenHeight;
//	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
//
//	if (nullptr == window)
//	{
//		cout << "Fialed to create window" << endl;
//		glfwTerminate();
//		return EXIT_FAILURE;
//	}
//	cout << "Window space is created" << endl;
//	glfwMakeContextCurrent(window);
//
//	glewExperimental = GL_TRUE;
//
//	if (GLEW_OK != glewInit())
//	{
//		cout << "Failed to initialise GLEW" << endl;
//		return EXIT_FAILURE;
//	}
//
//	glViewport(0, 0, screenWidth, screenHeight);
//
//	while (!glfwWindowShouldClose(window))
//	{
//		glfwPollEvents();
//		glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT);
//
//		glfwSwapBuffers(window);
//	}
//
//	glfwTerminate();
//	return EXIT_SUCCESS;
//}