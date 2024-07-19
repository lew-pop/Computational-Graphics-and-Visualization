#include "Shape.h"

// Default constructor
Shape::Shape() : model(0) {

}
Shape::Shape(bool isCylinder) {
    isCylinder = true;
}

// Destructor
Shape::~Shape() {

}

// Setters
void Shape::setModel(glm::vec3 position, glm::vec3 scale) {
    model = glm::translate(glm::mat4(1.0), position) * glm::scale(glm::mat4(1.0), scale);

}
void Shape::setObjectColor(glm::vec3  objectColor) {
    this->objectColor = objectColor;

}
void Shape::setLightColor(glm::vec3  lightColor) {
    this->lightColor = lightColor;

}
void Shape::setLightPos(glm::vec3  lightPos) {
    this->lightPos = lightPos;

}
void Shape::setViewPosition(glm::vec3  viewPos) {
    this->viewPosition = viewPos;

}
void Shape::setUVScale(glm::vec2  uvScale) {
    this->uvScale = uvScale;

}
void Shape::setScale(glm::vec3  scale) {
    this->scale = scale;
}
void Shape::setTranslate(glm::vec3  translate) {
    this->translate = translate;

}
void Shape::setRotate(float degree, glm::vec3  rotate) {
    this->rotate = rotate;
    rotateDegree = degree;

}
void Shape::setModelMatrix(Camera gCamera, glm::vec3 objectPosition, glm::vec3 objectScale) {
    model = glm::translate(objectPosition) * glm::scale(objectScale);
    view = gCamera.GetViewMatrix();
    projection = glm::perspective(glm::radians(gCamera.Zoom), (GLfloat)4 / (GLfloat)3, 0.1f, 100.0f);

}
void Shape::setShape(glm::vec3  objectColor, glm::vec3  lightColor, glm::vec3  lightPos, glm::vec3  cameraPosition, glm::vec2  uvScale) {
    setObjectColor(objectColor);
    setLightColor(lightColor);
    setLightPos(lightPos);
    setViewPosition(cameraPosition);
    setUVScale(uvScale);

}

// Getters
vector<GLfloat> Shape::getVertices() { return vertices; }
vector<GLushort> Shape::getIndices() { return indices; }
vector<GLfloat> Shape::getNormals() { return normals; }
glm::mat4 Shape::getModel() { return model; }
glm::mat4 Shape::getView() { return view; }
glm::mat4 Shape::getProjection() { return projection; }
glm::vec3 Shape::getObjectColor() { return objectColor; }
glm::vec3 Shape::getLightColor() { return lightColor; }
glm::vec3 Shape::getLightPos() { return lightPos; }
glm::vec3 Shape::getViewPosition() { return viewPosition; }
glm::vec2 Shape::getUVScale() { return uvScale; }
glm::vec3 Shape::getScale() { return scale; }
glm::vec3 Shape::getTranslate() { return translate; }
glm::vec3 Shape::getRotate() { return rotate; }
bool Shape::getIsCylinder() { return isCylinder; }
float Shape::getDegree() { return rotateDegree; }
