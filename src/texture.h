#ifndef TEXTURE_H
#define TEXTURE_H
#include "../lib/glad/include/glad/glad.h"
#include "structs.h"
#include <string>
#include <map>

class Texture {
public:
  Texture(std::map<std::string, ImageData*> imageData);
  std::map<std::string, int> getLayerMap();
  void bindTexture();
  void unbindTexture();
  void deleteTexture();
private:
  GLuint _ID;
  std::map<std::string, int> _layerMap;
};

#endif