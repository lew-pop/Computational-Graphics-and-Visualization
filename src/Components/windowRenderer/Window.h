#pragma once 
#include <stdio.h>
#include <iostream>

#include <GL/glew.h>        // GLEW library
#include <GLFW/glfw3.h>     // GLFW library

// GLM Headers
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

#include "camera.h"

using namespace std;

class Window {

public:

	// Constructor and Destructor
	Window();
	Window(Camera gCamera);
	~Window();

	// Getters 
	GLFWwindow* getWindow();
	GLint getWindowWidth();  // GLint getBufferWidth() { return bufferWidth; }
	GLint getWindowHeight(); //	GLint getBufferHeight() { return bufferHeight; }
	Camera getCamera();
	Camera getStaticCamera(Camera camera);
	GLfloat getXChange();
	GLfloat getYChange();

	// Setters
	void setWindow(GLFWwindow* window);
	void setDeltaTime(GLfloat gDeltaTime);
	void setLastFrame(GLfloat gLastFrame);
	void update(GLfloat gDeltaTime, GLfloat gLastFrame);

	// Global functions for GLFW window
	bool Initialize(int, char* []);
	void ProcessInput();


private:
	// Main GLFW window
	GLFWwindow* mainWindow;
	Camera mainCamera;

	GLint bufferWidth, bufferHeight;

	// Variables for window width and height
	GLint width, height;
	GLfloat xoffset, yoffset;
	GLfloat lastX, lastY;
	GLfloat deltaTime;
	GLfloat lastFrame;
	bool gFirstMouse;

	// Variable to hold window title
	const char* const WINDOW_TITLE = "3D Scene";

	// Constant variables for window width and height
	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 600;

	static void MousePositionCallback(GLFWwindow* window, double xpos, double ypos);
	static void MouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
	static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	static void ResizeWindow(GLFWwindow* window, int width, int height);
	
	
};