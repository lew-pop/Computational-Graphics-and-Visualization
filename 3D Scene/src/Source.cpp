#include <stdio.h>
#include <iostream>

#include "Window.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"

#include "Cylinder.h"
#include "Cube.h"

#include "camera.h"

//---------------------------------------------------------------------------------------------
//   Variables:
//---------------------------------------------------------------------------------------------    

	// Create Mesh, Camera, and Shader objects.
	Mesh gMesh;
	Shader shaderProgram;
    Camera camera (glm::vec3(0.0f, 5.0f, 15.0f));      

	// Timing
	GLfloat gDeltaTime = 0.0f;
	GLfloat gLastFrame = 0.0f;

	// Texture files 
	const char* backgroundFilename = "Textures/brownLeather.png";
	const char* coffeeMugFilename = "Textures/coffee_mug.png";
	const char* cologneBottleFilename = "Textures/cologne_bottle.png";
	const char* cologneTopFilename = "Textures/dark_silver_top.png";
	const char* calculatorFilename = "Textures/calcBody.png";
	const char* vitaminBottleFilename = "Textures/vitaminFlip.png";
	const char* vitaminNeckFilename = "Textures/vitaminNeck.png";
	const char* vitaminTopFilename = "Textures/blueTop.png";
	const char* mugHandleFilename = "Textures/glossWhite.png";
	const char* mugSecretFilename = "Textures/mugSecret.png";
	
	// Shader files
	const char* vertexShaderFilename = "Shaders/vertexShaderSource.vert";
	const char* fragmentShaderFilename = "Shaders/fragmentShaderSource.frag";
	/*
	const char* vertexShaderFilename = "Shaders/multipleLightShader.vert";
	const char* fragmentShaderFilename = "Shaders/multipleLightShader.frag";
	*/
	
//---------------------------------------------------------------------------------------------
// Arrays to hold and loop through vectors for affine transformations
//---------------------------------------------------------------------------------------------
	
	glm::vec3 objectScales[] = {
		glm::vec3(2.0f, 2.0f, 2.0f), // background
		glm::vec3(1.0f, 1.0f, 1.0f), // coffeeMug		
		glm::vec3(0.5f, 0.5f, 0.5f), // cologneBottle
		glm::vec3(0.5f, 0.5f, 0.5f), // cologneTop
		glm::vec3(0.5f, 0.5f, 0.5f), // calculator
		glm::vec3(1.0f, 1.0f, 1.0f), // vitaminBottle
		glm::vec3(1.0f, 1.0f, 1.0f), // vitaminBottle neck
		glm::vec3(1.0f, 1.0f, 1.0f), // vitaminBottle top
		
		
	
	};
	glm::vec3 objectPositions[] = {
		glm::vec3(0.0f, 0.0f, 0.0f),	// background
		glm::vec3(-3.5f, 1.5f, -1.0f),  // coffeeMug								
		glm::vec3(0.5, 0.75f, 0.5f),	// cologneBottle
		glm::vec3(0.5, 1.85f, 0.5f),	// cologneTop
		glm::vec3(3.0, 0.15f, 1.0f),	// calculator
		glm::vec3(6.0f, 1.25f, -2.5f),	// vitaminBottle
		glm::vec3(6.0f, 2.6f, -2.5f),	// vitaminBottle neck
		glm::vec3(6.0f, 3.0f, -2.5f),	// vitaminBottle top
										
	};									
	glm::vec3 objectRotations[] = {
		glm::vec3(1.1f, -1.0f, 1.0f),	// background
		glm::vec3(0.0f, 1.0f, 0.0f),	// coffeeMug
		glm::vec3(0.0f, 1.0f, 0.0f),	// cologneBottle
		glm::vec3(0.0f, 0.115f, 0.0f),	// cologneTop
		glm::vec3(0.0f, 1.0f, 0.0f),	// calculator
		glm::vec3(0.0f, 1.0f, 0.0f),	// vitaminBottle
		glm::vec3(0.0f, 1.0f, 0.0f),	// vitaminBottle neck
		glm::vec3(0.0f, 1.0f, 0.0f),	// vitaminBottle top
		
	};

	GLfloat rotateDegrees[] = { 90.0f, 90.0f, 25.0f, 90.0f, 25.0f, 15.0f, 15.0f, 25.0f, };

//---------------------------------------------------------------------------------------------
// Entry point to OpenGL program
//---------------------------------------------------------------------------------------------
int main(int argc, char* argv[])
{    

//---------------------------------------------------------------------------------------------
// Create and initialize GLFW Window and Shader programs
//---------------------------------------------------------------------------------------------	
    
	// Create the GLFW window
	Window mainWindow = Window(camera);
    if(!mainWindow.Initialize(argc, argv))
        return EXIT_FAILURE;

    // Create the shader program
    if (!shaderProgram.CreateShaderProgram(vertexShaderFilename, fragmentShaderFilename))
        return EXIT_FAILURE; 

//---------------------------------------------------------------------------------------------
// Load the textures
//---------------------------------------------------------------------------------------------
	Texture backgroundTexture;
	if (!backgroundTexture.CreateTexture(backgroundFilename, true))
	{
		cout << "Failed to load texture " << backgroundFilename << endl;
		return EXIT_FAILURE;
	}
	Texture coffeeMugTexture;
	if (!coffeeMugTexture.CreateTexture(coffeeMugFilename, true))
	{
		cout << "Failed to load texture " << coffeeMugFilename << endl;
		return EXIT_FAILURE;
	}
	Texture cologneBottleTexture;
	if (!cologneBottleTexture.CreateTexture(cologneBottleFilename, true))
	{
		cout << "Failed to load texture " << cologneBottleFilename << endl;
		return EXIT_FAILURE;
	}
	Texture cologneTopTexture;
	if (!cologneTopTexture.CreateTexture(cologneTopFilename, true))
	{
		cout << "Failed to load texture " << cologneTopFilename << endl;
		return EXIT_FAILURE;
	}	
	Texture calculatorTexture;
	if (!calculatorTexture.CreateTexture(calculatorFilename, true))
	{
		cout << "Failed to load texture " << calculatorFilename << endl;
		return EXIT_FAILURE;
	}
	Texture vitaminBottleTexture;
	if (!vitaminBottleTexture.CreateTexture(vitaminBottleFilename, true))
	{
		cout << "Failed to load texture " << vitaminBottleFilename << endl;
		return EXIT_FAILURE;
	}
	Texture vitaminNeckTexture;
	if (!vitaminNeckTexture.CreateTexture(vitaminNeckFilename, true))
	{
		cout << "Failed to load texture " << vitaminNeckFilename << endl;
		return EXIT_FAILURE;
	}
	Texture vitaminTopTexture;
	if (!vitaminTopTexture.CreateTexture(vitaminTopFilename, true))
	{
		cout << "Failed to load texture " << vitaminTopFilename << endl;
		return EXIT_FAILURE;
	}
	Texture mugHandleTexture;
	if (!mugHandleTexture.CreateTexture(mugHandleFilename, true))
	{
		cout << "Failed to load texture " << mugHandleFilename << endl;
		return EXIT_FAILURE;
	}
	Texture mugSecretTexture;
	if (!mugSecretTexture.CreateTexture(mugSecretFilename, true))
	{
		cout << "Failed to load texture " << mugSecretFilename << endl;
		return EXIT_FAILURE;
	}
//---------------------------------------------------------------------------------------------
// Create the mesh and shapes for 3D objects. 
//---------------------------------------------------------------------------------------------
	Mesh* backgroundObj = new Mesh();
	Cube background(2.0f, 5.0f, 0.0f);
	backgroundObj->initializeBuffers(background.getVertices());

	Mesh* coffeeMugObj = new Mesh();
	Cylinder coffeeMug(1.5f, 3.0f, 36);
	coffeeMugObj->initializeBuffers(coffeeMug.getVertices(), coffeeMug.getIndices());	

	Mesh* cologneBottleObj = new Mesh();
	Cube cologneBottle(1.0f, 1.5f, 0.5f);
	cologneBottleObj->initializeBuffers(cologneBottle.getVertices());

	Mesh* cologneTopObj = new Mesh();
	Cylinder cologneTop(0.5f, 1.4f, 36);
	cologneTopObj->initializeBuffers(cologneTop.getVertices(), cologneTop.getIndices());

	Mesh* calculatorObj = new Mesh();
	Cube calculator(true, 2.0f, 0.25f, 5.0f);
	calculatorObj->initializeBuffers(calculator.getVertices());	
	
	Mesh* vitaminBottleObj = new Mesh();
	Cylinder vitaminBottle(1.0f, 2.5f, 36);
	vitaminBottleObj->initializeBuffers(vitaminBottle.getVertices(), vitaminBottle.getIndices());

	Mesh* vitaminNeckObj = new Mesh();
	Cylinder vitaminNeck(0.9f, 0.4f, 36);
	vitaminNeckObj->initializeBuffers(vitaminNeck.getVertices(), vitaminNeck.getIndices());

	Mesh* vitaminTopObj = new Mesh();
	Cylinder vitaminTop(1.0f, 0.7f, 36);
	vitaminTopObj->initializeBuffers(vitaminTop.getVertices(), vitaminTop.getIndices());

	Mesh* coffeeMugHandleObj = new Mesh();
	Cylinder coffeeMugHandle(1.4f, 0.25f, 36);
	coffeeMugHandle.setScale(glm::vec3(1.0f, 1.0f, 1.0f));
	coffeeMugHandle.setTranslate(glm::vec3(-4.5f, 1.5f, -0.5f));
	coffeeMugHandleObj->initializeBuffers(coffeeMugHandle.getVertices(), coffeeMugHandle.getIndices());

	Mesh* coffeeMugSecretObj = new Mesh();
	Cylinder coffeeMugSecret(1.0f, 0.30f, 36);
	coffeeMugSecret.setScale(glm::vec3(0.5f, 0.5f, 0.5f));
	coffeeMugSecret.setTranslate(glm::vec3(-4.5f, 1.5f, -0.5f));
	coffeeMugSecretObj->initializeBuffers(coffeeMugSecret.getVertices(), coffeeMugSecret.getIndices());		

//-----------------------------------------------------------------------------------------------------
// Create arrays to hold and loop through mesh, texture, and shape objects.
// 	Set values for transformations. Transformation values are set in shape class. 
//-----------------------------------------------------------------------------------------------------
	Texture textureObjects[] = {
		backgroundTexture ,
		coffeeMugTexture,
		cologneBottleTexture,
		cologneTopTexture,
		calculatorTexture,
		vitaminBottleTexture,
		vitaminNeckTexture,
		vitaminTopTexture,
		
	};
	Mesh meshObjects[] = {
		*backgroundObj,
		*coffeeMugObj,
		*cologneBottleObj,
		*cologneTopObj,
		*calculatorObj,
		*vitaminBottleObj,
		*vitaminNeckObj,
		*vitaminTopObj,
		
	};
	Shape shapeObjects[] = {
		background,
		coffeeMug,
		cologneBottle,
		cologneTop,
		calculator,
		vitaminBottle,
		vitaminNeck,
		vitaminTop,
		
	};

	// Iterate objects and set scale, translate, and rotate tranformations 
	for (int i = 0; i < size(shapeObjects); i++) {
		shapeObjects[i].setScale(objectScales[i]);
		shapeObjects[i].setRotate(rotateDegrees[i], objectRotations[i]);
		shapeObjects[i].setTranslate(objectPositions[i]);

	}
//-----------------------------------------------------------------------------------------------------
// Loop while window is open
//-----------------------------------------------------------------------------------------------------
    while (!glfwWindowShouldClose(mainWindow.getWindow())) {
		// Calculate fps
		float currentFrame = glfwGetTime();
		gDeltaTime = currentFrame - gLastFrame;
		gLastFrame = currentFrame;	

		// Update the mainWindow's deltaTime and deltaFrame  
		mainWindow.update(gDeltaTime, gLastFrame);

		// Set background color
		glClearColor(0.08f, 0.08f, 0.08f, 1.0f);
		// Clear the background & Z buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Enable z-depth
		glEnable(GL_DEPTH_TEST);
		
        // Process inputs
        mainWindow.ProcessInput();				
		
		// Iterate objects to render mesh and texture
		for (auto i = 0; i < size(shapeObjects); i++) {
			meshObjects[i].renderMesh(shaderProgram, mainWindow.getCamera(), shapeObjects[i]);
			textureObjects[i].UseTexture();
			meshObjects[i].draw(shapeObjects[i].getIsCylinder());
			textureObjects[i].DestroyTexture();
		}	
		coffeeMugHandleObj->renderMesh(shaderProgram, mainWindow.getCamera(), coffeeMugHandle, true);
		mugHandleTexture.UseTexture();
		coffeeMugHandleObj->draw(true);
		mugHandleTexture.DestroyTexture();

		coffeeMugSecretObj->renderMesh(shaderProgram, mainWindow.getCamera(), coffeeMugSecret, true);
		mugSecretTexture.UseTexture();
		coffeeMugSecretObj->draw(true);
		mugSecretTexture.DestroyTexture();

        // Swap buffers and poll IO events
        glfwPollEvents(); 
        glfwSwapBuffers(mainWindow.getWindow());
       
    }	
	vitaminNeckObj->clearMesh();
	vitaminTopObj->clearMesh();
	vitaminBottleObj->clearMesh();
	calculatorObj->clearMesh();
	cologneTopObj->clearMesh();
	cologneBottleObj->clearMesh();
    coffeeMugObj->clearMesh();
	backgroundObj->clearMesh();

    // Terminates the program successfully
    exit(EXIT_SUCCESS); 
}




