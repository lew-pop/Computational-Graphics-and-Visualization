#pragma once
#include <iostream>
#include <vector>

#include "Shader.h"
#include "Texture.h"
#include "Window.h"

#include "Cylinder.h"
#include "Cube.h"

using namespace std;

class Mesh {

public:

	Mesh();
	~Mesh();
	
	void initializeBuffers(vector<GLfloat> vertices);
	void initializeBuffers(vector<GLfloat> vertices, vector<GLushort> index);
	void renderMesh(Shader shader, Camera gCamera, Shape shape);
	void renderMesh(Shader shader, Camera gCamera, Shape shape,bool noRotate);

	void clearMesh();
	void draw(bool isCylinder);

private:

	GLuint VAO, VBO;
	GLuint VBOS[2];	
	GLuint nIndices, nVertices;


	
};