#pragma once

#include <GL/glew.h>     // GLEW library
#include <GLFW/glfw3.h>  // GLFW library

// GLM Headers
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

#include <iostream>
#include <cstdlib>   // EXIT_FAILURE
#include <vector>  // vector
#include <iomanip>
#include <cmath>

#include "camera.h"

using namespace std;

class Shape {
public:
    // Constructor
    Shape();
    Shape(bool isCylinder);
    // Destructor
    ~Shape();

    // Getters
    virtual vector<GLfloat> getVertices();
    virtual vector<GLushort> getIndices();
    virtual vector<GLfloat> getNormals();

    glm::mat4 getModel();
    glm::mat4 getView();
    glm::mat4 getProjection();
    glm::vec3 getObjectColor();
    glm::vec3 getLightColor();
    glm::vec3 getLightPos();
    glm::vec3 getViewPosition();
    glm::vec2 getUVScale();
    glm::vec3 getScale();
    glm::vec3 getTranslate();
    glm::vec3 getRotate();

    virtual bool getIsCylinder();
    float getDegree();
   
    // Setters
    void setRotate(float degree, glm::vec3  rotate);
    void setModel(glm::vec3 position, glm::vec3 scale);
    void setObjectColor(glm::vec3  objectColor);
    void setLightColor(glm::vec3  lightColor);
    void setLightPos(glm::vec3  lightPos);
    void setViewPosition(glm::vec3  viewPos);
    void setUVScale(glm::vec2  uvScale);
    void setScale(glm::vec3  scale);
    void setTranslate(glm::vec3  translate);
    void setModelMatrix(Camera gCamera, glm::vec3 objectPosition, glm::vec3 objectScale);
    void setShape(glm::vec3  objectColor, glm::vec3  lightColor, glm::vec3  lightPos, glm::vec3  cameraPosition, glm::vec2  uvScale);
   
    bool isCylinder;

private:
    glm::vec2 uvScale;
    glm::vec3 scale, translate, rotate;
    glm::vec3  objectColor, lightColor, lightPos, viewPosition;
    glm::mat4 model, view, projection;
    
    vector<GLfloat> vertices, normals;
    vector<GLushort> indices;

    float rotateDegree;
   
};
