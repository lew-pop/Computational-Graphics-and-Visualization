#include "Cube.h"

Cube::Cube(float length, float height, float width) {
	set(length, height, width);
	initializeData();
}
Cube::Cube(bool noRepeat, float length, float height, float width) {
	set(length, height, width);
	initializeData(noRepeat);
}
void Cube::set(float length, float height, float width) {
	this->length = length;
	this->height = height;
	this->width = width;
}
const float Cube::getLength() { return length; }
const float Cube::getHeight() { return height; }
const float Cube::getWidth() { return width; }

vector<GLfloat> Cube::getVertices() { return vertices; }
vector<GLushort> Cube::getIndices() {
	GLushort indicesArray[36] = { 0, 1, 2,
								1, 2, 3,
								0, 2, 6,
								0, 4, 6,
								0, 4, 5,
								0, 1, 5,
								1, 3, 7,
								1, 5, 7,
								4, 6, 7,
								4, 5, 7,
								2, 6, 7,
								2, 3, 7 };

	indices.insert(indices.begin(), begin(indicesArray), end(indicesArray));

	return indices;
}
void Cube::setLength(float length) {
	if (this->length != length) set(length, height, width);
}

void Cube::setHeight(float height) {
	if (this->height != height) set(length, height, width);
}

void Cube::setWidth(float width) {
	if (this->width != width) set(length, height, width);
}
void Cube::initializeData() {
	vector<GLfloat>().swap(vertices);

	xPos = length;
	yPos = height;
	zPos = width;

	// Front top left
	frontTopLeft.push_back(-xPos);
	frontTopLeft.push_back(yPos);
	frontTopLeft.push_back(zPos);
	// Front top right
	frontTopRight.push_back(xPos);
	frontTopRight.push_back(yPos);
	frontTopRight.push_back(zPos);
	// Front bottom left
	frontBottomLeft.push_back(-xPos);
	frontBottomLeft.push_back(-yPos);
	frontBottomLeft.push_back(zPos);
	// Front bottom right
	frontBottomRight.push_back(xPos);
	frontBottomRight.push_back(-yPos);
	frontBottomRight.push_back(zPos);
	// Back top left
	backTopLeft.push_back(-xPos);
	backTopLeft.push_back(yPos);
	backTopLeft.push_back(-zPos);
	// Back top right
	backTopRight.push_back(xPos);
	backTopRight.push_back(yPos);
	backTopRight.push_back(-zPos);
	// Back bottom left
	backBottomLeft.push_back(-xPos);
	backBottomLeft.push_back(-yPos);
	backBottomLeft.push_back(-zPos);
	// Back bottom right
	backBottomRight.push_back(xPos);
	backBottomRight.push_back(-yPos);
	backBottomRight.push_back(-zPos);

	// Front face
	generateVertexData(frontTopLeft, "front", 0.0f, 1.0f);
	generateVertexData(frontTopRight, "front", 1.0f, 1.0f);
	generateVertexData(frontBottomLeft, "front", 0.0f, 0.0f);

	generateVertexData(frontBottomLeft, "front", 0.0f, 0.0f);
	generateVertexData(frontBottomRight, "front", 1.0f, 0.0f);
	generateVertexData(frontTopRight, "front", 1.0f, 1.0f);

	// Right face
	generateVertexData(backTopRight, "right", 0.0f, 1.0f);
	generateVertexData(frontTopRight, "right", 0.0f, 1.0f);
	generateVertexData(backBottomRight, "right", 0.0f, 0.0f);
	generateVertexData(backBottomRight, "right", 0.0f, 0.0f);
	generateVertexData(frontBottomRight, "right", 0.0f, 0.0f);
	generateVertexData(frontTopRight, "right", 0.0f, 1.0f);

	// Back face
	generateVertexData(backTopLeft, "back", 0.0f, 1.0f);
	generateVertexData(backTopRight, "back", 1.0f, 1.0f);
	generateVertexData(backBottomLeft, "back", 0.0f, 0.0f);

	generateVertexData(backBottomLeft, "back", 0.0f, 0.0f);
	generateVertexData(backBottomRight, "back", 1.0f, 0.0f);
	generateVertexData(backTopRight, "back", 1.0f, 1.0f);

	// Left face
	generateVertexData(backTopLeft, "left", 0.0f, 1.0f);
	generateVertexData(frontTopLeft, "left", 0.0f, 1.0f);
	generateVertexData(backBottomLeft, "left", 0.0f, 0.0f);
	generateVertexData(backBottomLeft, "left", 0.0f, 0.0f);
	generateVertexData(frontBottomLeft, "left", 0.0f, 0.0f);
	generateVertexData(frontTopLeft, "left", 0.0f, 1.0f);

	// Top face
	generateVertexData(frontTopLeft, "top", 0.0f, 0.0f);
	generateVertexData(frontTopRight, "top", 1.0f, 0.0f);
	generateVertexData(backTopLeft, "top", 0.0f, 1.0f);

	generateVertexData(backTopLeft, "top", 0.0f, 1.0f);
	generateVertexData(backTopRight, "top", 1.0f, 1.0f);
	generateVertexData(frontTopRight, "top", 1.0f, 0.0f);

	// Bottom face
	generateVertexData(frontBottomLeft, "bottom", 0.0f, 0.0f);
	generateVertexData(frontBottomRight, "bottom", 1.0f, 0.0f);
	generateVertexData(backBottomLeft, "bottom", 0.0f, 1.0f);

	generateVertexData(backBottomLeft, "bottom", 0.0f, 1.0f);
	generateVertexData(backBottomRight, "bottom", 1.0f, 1.0f);
	generateVertexData(frontBottomRight, "bottom", 1.0f, 0.0f);

}
void Cube::initializeData(bool noRepeat) {
	vector<GLfloat>().swap(vertices);

	xPos = length;
	yPos = height;
	zPos = width;

	// Front top left
	frontTopLeft.push_back(-xPos);
	frontTopLeft.push_back(yPos);
	frontTopLeft.push_back(zPos);
	// Front top right
	frontTopRight.push_back(xPos);
	frontTopRight.push_back(yPos);
	frontTopRight.push_back(zPos);
	// Front bottom left
	frontBottomLeft.push_back(-xPos);
	frontBottomLeft.push_back(-yPos);
	frontBottomLeft.push_back(zPos);
	// Front bottom right
	frontBottomRight.push_back(xPos);
	frontBottomRight.push_back(-yPos);
	frontBottomRight.push_back(zPos);
	// Back top left
	backTopLeft.push_back(-xPos);
	backTopLeft.push_back(yPos);
	backTopLeft.push_back(-zPos);
	// Back top right
	backTopRight.push_back(xPos);
	backTopRight.push_back(yPos);
	backTopRight.push_back(-zPos);
	// Back bottom left
	backBottomLeft.push_back(-xPos);
	backBottomLeft.push_back(-yPos);
	backBottomLeft.push_back(-zPos);
	// Back bottom right
	backBottomRight.push_back(xPos);
	backBottomRight.push_back(-yPos);
	backBottomRight.push_back(-zPos);

	// Front face
	generateVertexData(frontTopLeft, "front", 0.0f, 1.0f);
	generateVertexData(frontTopRight, "front", 0.0f, 1.0f);
	generateVertexData(frontBottomLeft, "front", 0.0f, 0.0f);
	generateVertexData(frontBottomLeft, "front", 0.0f, 0.0f);
	generateVertexData(frontBottomRight, "front", 0.0f, 0.0f);
	generateVertexData(frontTopRight, "front", 0.0f, 1.0f);

	// Right face
	generateVertexData(backTopRight, "right", 0.0f, 1.0f);
	generateVertexData(frontTopRight, "right", 0.0f, 1.0f);
	generateVertexData(backBottomRight, "right", 0.0f, 0.0f);
	generateVertexData(backBottomRight, "right", 0.0f, 0.0f);
	generateVertexData(frontBottomRight, "right", 0.0f, 0.0f);
	generateVertexData(frontTopRight, "right", 0.0f, 1.0f);

	// Back face
	generateVertexData(backTopLeft, "back", 0.0f, 1.0f);
	generateVertexData(backTopRight, "back", 0.0f, 1.0f);
	generateVertexData(backBottomLeft, "back", 0.0f, 0.0f);
	generateVertexData(backBottomLeft, "back", 0.0f, 0.0f);
	generateVertexData(backBottomRight, "back", 0.0f, 0.0f);
	generateVertexData(backTopRight, "back", 0.0f, 1.0f);

	// Left face
	generateVertexData(backTopLeft, "left", 0.0f, 1.0f);
	generateVertexData(frontTopLeft, "left", 0.0f, 1.0f);
	generateVertexData(backBottomLeft, "left", 0.0f, 0.0f);
	generateVertexData(backBottomLeft, "left", 0.0f, 0.0f);
	generateVertexData(frontBottomLeft, "left", 0.0f, 0.0f);
	generateVertexData(frontTopLeft, "left", 0.0f, 1.0f);

	// Top face
	generateVertexData(frontTopLeft, "top", 0.0f, 0.0f);
	generateVertexData(frontTopRight, "top", 1.0f, 0.0f);
	generateVertexData(backTopLeft, "top", 0.0f, 1.0f);

	generateVertexData(backTopLeft, "top", 0.0f, 1.0f);
	generateVertexData(backTopRight, "top", 1.0f, 1.0f);
	generateVertexData(frontTopRight, "top", 1.0f, 0.0f);

	// Bottom face
	generateVertexData(frontBottomLeft, "bottom", 0.0f, 0.0f);
	generateVertexData(frontBottomRight, "bottom", 1.0f, 0.0f);
	generateVertexData(backBottomLeft, "bottom", 0.0f, 1.0f);

	generateVertexData(backBottomLeft, "bottom", 0.0f, 1.0f);
	generateVertexData(backBottomRight, "bottom", 1.0f, 1.0f);
	generateVertexData(frontBottomRight, "bottom", 1.0f, 0.0f);

}
void Cube::pushCoords(vector<float> coords) {
	for (int i = 0; i < coords.size(); i++) {
		vertices.push_back(coords.at(i));
	}
}

void Cube::pushNormals(string side) {

	if (side == "front") {
		vertices.push_back(0.0f);
		vertices.push_back(0.0f);
		vertices.push_back(1.0f);
	}
	else if (side == "back") {
		vertices.push_back(0.0f);
		vertices.push_back(0.0f);
		vertices.push_back(-1.0f);
	}
	else if (side == "right") {
		vertices.push_back(1.0f);
		vertices.push_back(0.0f);
		vertices.push_back(0.0f);
	}
	else if (side == "left") {
		vertices.push_back(-1.0f);
		vertices.push_back(0.0f);
		vertices.push_back(0.0f);
	}
	else if (side == "top") {
		vertices.push_back(0.0f);
		vertices.push_back(1.0f);
		vertices.push_back(0.0f);
	}
	else if (side == "bottom") {
		vertices.push_back(0.0f);
		vertices.push_back(-1.0f);
		vertices.push_back(0.0f);
	}
	else {
		cout << "ERROR: Could not add normals to vertex data!" << endl;
	}
}

void Cube::pushTexCoords(float x, float y) {
	vertices.push_back(x);
	vertices.push_back(y);
}

void Cube::generateVertexData(vector<float> coords, string side, float x, float y) {
	pushCoords(coords);
	pushNormals(side);
	pushTexCoords(x, y);
}


