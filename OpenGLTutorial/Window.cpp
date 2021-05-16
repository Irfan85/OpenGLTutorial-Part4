#include "Window.h"

Window::Window()
{
	width = 800;
	height = 600;
}

Window::Window(GLint windowWidth, GLint windowHeight)
{
	width = windowWidth;
	height = windowHeight;
}

int Window::Initialize()
{
	if (!glfwInit())
	{
		printf("GLFW initialization failed");
		glfwTerminate();
		return 1;
	}

	// Setup GLFW window properties
	// OpenGL version (We're choosing version 3.3)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// We're setting our OpenGL profile to use just core features to avoid all the old and deprecated features.
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// We want out program to be forward compatible
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	
	// Creating the window
	mainWindow = glfwCreateWindow(width, height, "Test Window", NULL, NULL);
	if (!mainWindow)
	{
		printf("GLFW window creation failed!");
		glfwTerminate();
		return 1;
	}
	
	// Get Buffer size information
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	// Set context for GLEW to use
	glfwMakeContextCurrent(mainWindow);

	// Allow mordern extension features (These are experimental features)
	glewExperimental = GL_TRUE;
	
	// Check for errors
	GLenum error = glewInit();
	if (glewInit() != GLEW_OK)
	{
		printf("Error: %s", glewGetErrorString(error));
		// Destroy the window and then GLFW
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}
	
	// Will enable depth for vertices
	glEnable(GL_DEPTH_TEST);

	// Create viewport
	glViewport(0, 0, bufferWidth, bufferHeight);
	
//	return 0;
}

Window::~Window()
{
	glfwDestroyWindow(mainWindow);
	glfwTerminate();
}
