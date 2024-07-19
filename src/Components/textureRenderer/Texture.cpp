#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"      // Image loading Utility functions

// Constructor
Texture::Texture() : textureId(0) {
  
}
// Destructor
Texture::~Texture() {
    glGenTextures(1, &textureId);
}

bool Texture::CreateTexture(const char* fileName, bool generateMipMaps) {

    int width, height, channels;

    // STBI image library to load image
    unsigned char *image = stbi_load(fileName, &width, &height, &channels, 0);

  if (image) {
    flipImageVertically(image, width, height, channels);

    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_LINEAR);
  


    if (channels == 3)
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB,
                   GL_UNSIGNED_BYTE, image);
    else if (channels == 4)
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA,
                   GL_UNSIGNED_BYTE, image);
    else {
      cout << "Not implemented to handle image with " << channels << " channels"
           << endl;
      return false;
    }
    if(generateMipMaps)
        glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(image);
    glBindTexture(GL_TEXTURE_2D, 0);  // Unbind the texture

    return true;
  }
  // Error loading the image
  return false;
}

void Texture::UseTexture() {
 // assert(texUnit >= 0 && texUnit < 32);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId);
  
}

void Texture::DestroyTexture() {
  glActiveTexture(GL_TEXTURE0 );
  glBindTexture(GL_TEXTURE_2D, 0);
}

// Images are loaded with Y axis going down, but OpenGL's Y axis goes up, so
// let's flip it
void Texture::flipImageVertically(unsigned char *image, int width, int height,
                                  int channels) {
  for (int j = 0; j < height / 2; ++j) {
    int index1 = j * width * channels;
    int index2 = (height - 1 - j) * width * channels;

    for (int i = width * channels; i > 0; --i) {
      unsigned char tmp = image[index1];
      image[index1] = image[index2];
      image[index2] = tmp;
      ++index1;
      ++index2;
    }
  }
}