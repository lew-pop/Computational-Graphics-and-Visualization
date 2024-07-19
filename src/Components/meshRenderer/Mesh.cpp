#include "Mesh.h"

// Constructor
Mesh::Mesh(){
    //nIndices = 0;
    nVertices = 0;
    VAO = 0;
    VBO = 0;
    //VBOS[2] = {};
}

// Destructor
Mesh::~Mesh(){
    clearMesh();
}

void Mesh::initializeBuffers(vector<GLfloat> vertices) {
    
    GLfloat verts[600] = { };
    copy(vertices.begin(), vertices.end(), verts);
    // Create the Vertex Attribute Pointer for the screen coordinates
    const GLuint floatsPerVertex = 3;
    const GLuint floatsPerNormal = 3;
    const GLuint floatsPerUV = 2;

    nVertices = sizeof(verts) / (sizeof(verts[0]) * (floatsPerVertex + floatsPerNormal + floatsPerUV));

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);                  // Create 2 buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO); // Activate the buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts,
        GL_STATIC_DRAW); // Sends vertex data to the GPU

    // Strides between vertex coordinates
    GLint stride = sizeof(float) * (floatsPerVertex + floatsPerNormal + floatsPerUV);// The number of floats before each

    // Create Vertex Attribute Pointers
    glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, floatsPerNormal, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * floatsPerVertex));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, floatsPerUV, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * (floatsPerVertex + floatsPerNormal)));
    glEnableVertexAttribArray(2);
}

void Mesh::initializeBuffers(vector<GLfloat> vertices, vector<GLushort> index) {
       
    // Create an array for buffer object data for the vertices
    GLfloat verts[800] = { };
    copy(vertices.begin(), vertices.end(), verts);

    // Create an array for buffer object data for the indices
    GLushort indices[600] = { };
    copy(index.begin(), index.end(), indices);

    // Create the Vertex Attribute Pointer for the screen coordinates
    const GLuint floatsPerVertex = 3; // Number of coordinates per vertex
    const GLuint floatsPerUV = 2;

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(2, VBOS);                  // Create 2 buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBOS[0]); // Activate the buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts,
        GL_STATIC_DRAW); // Sends vertex data to the GPU

    nIndices = sizeof(indices) / sizeof(indices[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBOS[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
        GL_STATIC_DRAW);

    // Strides between vertex coordinates
    GLint stride = sizeof(float) * (floatsPerVertex + floatsPerUV);

    // Create the Vertex Attribute Pointers
    glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(2, floatsPerUV, GL_FLOAT, GL_FALSE, stride,
        (char*)(sizeof(float) * floatsPerVertex));
    glEnableVertexAttribArray(2);
}

// Functioned called to render a frame
void Mesh::renderMesh(Shader shader, Camera gCamera, Shape shape){    
   
    // Scale triangle down by half
    glm::mat4 scale = glm::scale(shape.getScale());

    // Rotate triangle by 15 degrees on the y axis
    glm::mat4 rotation = glm::rotate(shape.getDegree(), shape.getRotate());

    // Translate triangle at the origin
    glm::mat4 translation = glm::translate(shape.getTranslate());

    // Model matrix: Transformations
    glm::mat4 model = translation * rotation * scale;

    // camera/view transformation
    glm::mat4 view = gCamera.GetViewMatrix();

    // Creates a perspective projection
    glm::mat4 projection = glm::perspective(glm::radians(gCamera.Zoom), (GLfloat)4 / (GLfloat)3, 0.1f, 100.0f);

    glUseProgram(shader.getProgram());

    // Retrieves and passes transform matrices to the Shader program
    GLint modelLoc = glGetUniformLocation(shader.getProgram(), "model");
    GLint viewLoc = glGetUniformLocation(shader.getProgram(), "view");
    GLint projLoc = glGetUniformLocation(shader.getProgram(), "projection");

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

    // Activate the VBOs contained within the mesh's VAO
    glBindVertexArray(VAO);

    // Deactivate the Vertex Array Object
    glBindVertexArray(0);
   
}
void Mesh::renderMesh(Shader shader, Camera gCamera, Shape shape, bool noRotate) {
    // Scale triangle down by half
   // glm::mat4 scale = glm::scale(shape.getScale());

    // Translate triangle at the origin
    glm::mat4 translation = glm::translate(shape.getTranslate());
    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(1.0, 0.0, -0.45));
    trans = glm::scale(trans, glm::vec3(1.0, 1.0, 1.0));
    // Model matrix: Transformations
    glm::mat4 model = translation * trans;

    // camera/view transformation
    glm::mat4 view = gCamera.GetViewMatrix();

    // Creates a perspective projection
    glm::mat4 projection = glm::perspective(glm::radians(gCamera.Zoom), (GLfloat)4 / (GLfloat)3, 0.1f, 100.0f);

    glUseProgram(shader.getProgram());

    // Retrieves and passes transform matrices to the Shader program
    GLint modelLoc = glGetUniformLocation(shader.getProgram(), "model");
    GLint viewLoc = glGetUniformLocation(shader.getProgram(), "view");
    GLint projLoc = glGetUniformLocation(shader.getProgram(), "projection");

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

    // Activate the VBOs contained within the mesh's VAO
    glBindVertexArray(VAO);

    // Deactivate the Vertex Array Object
    glBindVertexArray(0);
}

void Mesh::draw(bool isCylinder)
{
    glBindVertexArray(VAO);
    if (isCylinder) {
        // Draws the triangle
        glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_SHORT,
            NULL);
    }
    else {
        // Draws the triangle
        glDrawArrays(GL_TRIANGLES, 0, nVertices);

    }
    glBindVertexArray(0);
}

void Mesh::clearMesh()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}