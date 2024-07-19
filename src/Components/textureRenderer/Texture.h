#ifndef TEXTURE_H
#define TEXTURE_H
#include <GL/glew.h>     // GLEW library
#include <GLFW/glfw3.h>  // GLFW library

#include <iostream>  // cout, cerr
#include <cassert>
#include <cstdlib> 
// GLM Headers
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

using namespace std;

class Texture
{
	public:
	Texture();
	~Texture();
	
	bool CreateTexture(const char* fileName, bool generateMipMaps = true);
	void UseTexture();
	void DestroyTexture();
	
	private:
	GLuint textureId;
	

	//Texture(const Texture &rhs) {}
	//Texture &operator = (const Texture &rhs) {}
	
	void flipImageVertically(unsigned char *image, int width, int height, int channels);
};
#endif // TEXTURE_H
