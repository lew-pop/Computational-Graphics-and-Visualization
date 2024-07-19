#pragma once
#include <GL/glew.h>     // GLEW library
#include <GLFW/glfw3.h>  // GLFW library

#include <cstdlib>   // EXIT_FAILURE
#include <iostream>  // cout, cerr
#include <vector>    // vector

// GLM Headers
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

#include <iostream>
#include <iomanip>
#include <cmath>
#include "Shape.h"

using namespace std;

class Cube : public Shape {
public:
	// Constructor
	Cube(float length = 1.0f, float height = 1.0f,
		float width = 1.0f);
	Cube(bool noRepeat, float length = 1.0f, float height = 1.0f,
		float width = 1.0f);
	// Destructor
	~Cube() {}

	// Getters
	const float getLength();
	const float getHeight();
	const float getWidth();

	vector<GLfloat> getVertices() override;
	vector<GLushort> getIndices() override;
	

	// Setters
	void set(float length, float height,
		float width);
	void setLength(float length);
	void setHeight(float height);
	void setWidth(float width);



private:
	// memeber variables
	float length, height, width;
	float xPos, yPos, zPos;

	vector<GLfloat> vertices;
	vector<GLushort> indices;

	vector<float> frontTopLeft, frontTopRight, frontBottomLeft, 
					frontBottomRight, backTopLeft, backTopRight, 
					 backBottomLeft, backBottomRight;
	
	void initializeData();
	void initializeData(bool noRepeat);

	void pushCoords(vector<float> coords);
	void pushNormals(string side);
	void pushTexCoords(float x, float y);
	void generateVertexData(vector<float> coords, string side, float x, float y);

};
