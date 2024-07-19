#include "Cylinder.h"


Cylinder::Cylinder(float radius, float height, int sectors) : Shape(isCylinder = true) {
	this->_radius = radius;
	this->_height = height;
	this->_sectorCount = sectors;
	initializeCylinder();
}

// Getters
const float Cylinder::getRadius() { return _radius; }
const float Cylinder::getHeight() { return _height; }
const int Cylinder::getSectorCount() { return _sectorCount; }
vector<GLfloat> Cylinder::getVertices() { return verts; }
vector<GLushort> Cylinder::getIndices() { return indices; }

// Initialize data for cylinder 
void Cylinder::initializeCylinder() {
	// Calculate and cache numbers of vertices
	_sideVertCount = (_sectorCount + 1) * 2;
	_baseVertCount = _sectorCount + 2;
	_totalVertCount = _sideVertCount + _baseVertCount * 2;

	vector<float> sines, cosines;
	const auto sectorStep = 2.0f * glm::pi<float>() / float(_sectorCount);
	auto currentSector = 0.0f;

	for (int i = 0; i < _sectorCount; i++)
	{
		sines.push_back(sin(currentSector));
		cosines.push_back(cos(currentSector));

		// Update slice angle
		currentSector += sectorStep;
	}

	// Pre-calculate X and Z coordinates
	vector<float> x;
	vector<float> z;
	int indexCount;
	for (int i = 0; i < _sectorCount; i++)
	{
		x.push_back(cosines[i] * _radius);
		z.push_back(sines[i] * _radius);
	}

	// Add cylinder side vertices
	for (int i = 0; i < _sectorCount; i++)
	{

		// Coordinates for top of cylinder
		verts.push_back(x[i]);
		verts.push_back(_height / 2.0f);
		verts.push_back(z[i]);

		verts.push_back((float)i / _sectorCount);
		verts.push_back(1.0f);

		// Coordinates for bottom of cylinder
		verts.push_back(x[i]);
		verts.push_back(-_height / 2.0f);
		verts.push_back(z[i]);

		verts.push_back((float)i / _sectorCount);
		verts.push_back(0.0f);


	}
	indexCount = _sectorCount * 2;
	for (int i = 0; i < indexCount - 1; i++) {
		if (i == indexCount - 2) {
			indices.push_back(0);
			indices.push_back(1);
			indices.push_back(i + 1);

			indices.push_back(0);
			indices.push_back(i);
			indices.push_back(i + 1);
		}
		else {
			indices.push_back(i);
			indices.push_back(i + 1);
			indices.push_back(i + 2);
		}
	}
	// Add top cylinder cover	
	verts.push_back(0.0f);
	verts.push_back(_height / 2.0f);
	verts.push_back(0.0f);
	verts.push_back(0.5f);
	verts.push_back(1.0f);


	for (int i = 0; i < indexCount - 1; i += 2) {
		if (i == indexCount - 2) {
			indices.push_back(indexCount);
			indices.push_back(0);
			indices.push_back(i);
		}
		else {
			indices.push_back(indexCount);
			indices.push_back(i);
			indices.push_back(i + 2);
		}
	}
	// Add bottom cylinder cover
	verts.push_back(0.0f);
	verts.push_back(-_height / 2.0f);
	verts.push_back(0.0f);
	verts.push_back(0.5f);
	verts.push_back(0.0f);



	for (int i = 1; i < indexCount; i += 2) {
		if (i == indexCount - 1) {
			indices.push_back(indexCount + 1);
			indices.push_back(1);
			indices.push_back(i);
		}
		else {
			indices.push_back(indexCount + 1);
			indices.push_back(i);
			indices.push_back(i + 2);
		}
	}

}

