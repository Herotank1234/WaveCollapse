#ifndef TEXTURE_H
#define TEXTURE_H
#include "../lib/glad/include/glad/glad.h"
#include "structs.h"

class Texture {
public:
  Texture();
  void changeTexture(ImageData* imgData);
  void bindTexture();
  void unbindTexture();
  void deleteTexture();
private:
  GLuint _ID;
};

#endif