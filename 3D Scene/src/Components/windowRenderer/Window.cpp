#include "Window.h"

// Constructor
Window::Window() {
	mainWindow = 0;
	width = 800;
	height = 600;
	deltaTime = 0.0f;
	lastFrame = 0.0f;
	gFirstMouse = true;
}
// Constructor
Window::Window(Camera gCamera) {
	mainWindow = 0;
	mainCamera = gCamera;
	width = 800;
	height = 600;
	deltaTime = 0.0f;
	lastFrame = 0.0f;
	gFirstMouse = true;
}

// Destructor
Window::~Window()
{
	glfwDestroyWindow(mainWindow);
	glfwTerminate();
}

// Getters
GLFWwindow* Window::getWindow() { return mainWindow; }
GLint Window::getWindowWidth() { return width; }
GLint Window::getWindowHeight() { return height; }
Camera Window::getCamera() { return mainCamera; }

GLfloat Window::getXChange()
{
	GLfloat theChange = xoffset;
	xoffset = 0.0f;
	return theChange;
}
GLfloat Window::getYChange()
{
	GLfloat theChange = yoffset;
	yoffset = 0.0f;
	return theChange;

}

//Setters
void Window::setDeltaTime(GLfloat gDeltaTime) {
	deltaTime = gDeltaTime;

}
void Window::setLastFrame(GLfloat gLastFrame) {
	lastFrame = gLastFrame;

}
void Window::update(GLfloat gDeltaTime, GLfloat gLastFrame) {
	setDeltaTime(gDeltaTime);
	setLastFrame(gLastFrame);
}

//--------------------------------------------------------------------
// Global GLFW functions
//--------------------------------------------------------------------

// Initialize GLFW, GLEW, and create a window
bool Window::Initialize(int argc, char* argv[]) {
	// Initialize the GLFW library
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// Create GFLW Window
	mainWindow =
		glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
	if (!mainWindow) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}
	// Get buffer size information
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);
	// Make the window's context current
	glfwMakeContextCurrent(mainWindow);
	//glfwGetWindowUserPointer(mainWindow);
	glfwSetFramebufferSizeCallback(mainWindow, ResizeWindow);
	glfwSetCursorPosCallback(mainWindow, MousePositionCallback);
	glfwSetScrollCallback(mainWindow, MouseScrollCallback);
	glfwSetMouseButtonCallback(mainWindow, MouseButtonCallback);
	
	// GLFW mouse properties 
	glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Initialize the GLEW library
	glewExperimental = GL_TRUE;
	GLenum GlewInitResult = glewInit();

	if (GLEW_OK != GlewInitResult) {
		std::cerr << glewGetErrorString(GlewInitResult) << std::endl;
		return false;
	}
	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, bufferWidth, bufferHeight);
	glfwSetWindowUserPointer(mainWindow, this);

	// Displays GPU OpenGL version
	cout << "INFO: OpenGL Version: " << glGetString(GL_VERSION) << endl;

	return true;
}

// Process GLFW inputs 
void Window::ProcessInput()
{
	
	if (glfwGetKey(mainWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(mainWindow, true);
	if (glfwGetKey(mainWindow, GLFW_KEY_W) == GLFW_PRESS)
		mainCamera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(mainWindow, GLFW_KEY_S) == GLFW_PRESS)
		mainCamera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(mainWindow, GLFW_KEY_A) == GLFW_PRESS)
		mainCamera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(mainWindow, GLFW_KEY_D) == GLFW_PRESS)
		mainCamera.ProcessKeyboard(RIGHT, deltaTime);
	/* The Camera.h file has been modified. Adding UP and DOWN value options for camera movement */
	if (glfwGetKey(mainWindow, GLFW_KEY_Q) == GLFW_PRESS)
		mainCamera.ProcessKeyboard(UP, deltaTime);
	if (glfwGetKey(mainWindow, GLFW_KEY_E) == GLFW_PRESS)
		mainCamera.ProcessKeyboard(DOWN, deltaTime);
	
}

// Resize GLFW window
void Window::ResizeWindow(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);

}

// glfw: callback for mouse moves
void Window::MousePositionCallback(GLFWwindow* window, double xpos, double ypos)
{	
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
	if (theWindow->gFirstMouse)
	{
		theWindow->lastX = xpos;
		theWindow->lastY = ypos;
		theWindow->gFirstMouse = false;
	}
	 theWindow->xoffset = xpos - theWindow->lastX;
	 theWindow->yoffset = theWindow->lastY - ypos; 

	theWindow->lastX = xpos;
	theWindow->lastY = ypos;
	theWindow->mainCamera.ProcessMouseMovement(theWindow->xoffset, theWindow->yoffset);	
}

// glfw: callback for mouse scroll wheel
void Window::MouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
	if (yoffset) {
		theWindow->getCamera().ProcessMouseScroll(yoffset, theWindow->deltaTime);
	}
	if (xoffset) {
		theWindow->getCamera().ProcessMouseScroll(-xoffset, theWindow->deltaTime);
	}
}

// glfw: mouse button events
void Window::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	switch (button)
	{
	case GLFW_MOUSE_BUTTON_LEFT:
	{
		if (action == GLFW_PRESS)
			cout << "Left mouse button pressed" << endl;
		else
			cout << "Left mouse button released" << endl;
	}
	break;

	case GLFW_MOUSE_BUTTON_MIDDLE:
	{
		if (action == GLFW_PRESS)
			cout << "Middle mouse button pressed" << endl;
		else
			cout << "Middle mouse button released" << endl;
	}
	break;

	case GLFW_MOUSE_BUTTON_RIGHT:
	{
		if (action == GLFW_PRESS)
			cout << "Right mouse button pressed" << endl;
		else
			cout << "Right mouse button released" << endl;
	}
	break;

	default:
		cout << "Unhandled mouse button event" << endl;
		break;
	}
}






