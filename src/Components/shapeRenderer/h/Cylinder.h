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

class Cylinder : public Shape
{
public:
	// Constructor
	Cylinder(float radius = 1.0f, float height = 1.0f,
		int sectorCount = 36);

	// Destructor
	~Cylinder() {}

	// Getters
	const float getRadius();
	const float getHeight();
	const int getSectorCount();

	vector<GLfloat> getVertices() override;
	vector<GLushort> getIndices() override;



private:

	vector<GLfloat> verts;
	vector<GLushort> indices;


	float _radius;
	float _height;

	int _sectorCount;
	int _sideVertCount;
	int _baseVertCount;
	int _totalVertCount;

	void initializeCylinder();
};

