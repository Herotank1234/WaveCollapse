#include "texture.h"
#include <iostream>

Texture::Texture(std::map<std::string, ImageData*> imageMap) {
  glGenTextures(1, &_ID);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D_ARRAY, _ID);

  glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);

  int width = imageMap.begin()->second->width,
    height = imageMap.begin()->second->height;
  glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGB, width, height, imageMap.size(),
    0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
  
  int index = 0;
  for(auto it = imageMap.begin(); it != imageMap.end(); it++) {
    glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, index, width, height, 1, GL_RGB,
      GL_UNSIGNED_BYTE, it->second->bytes);
    _layerMap.insert({it->first, index++});
  }
  glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
}

std::map<std::string, int> Texture::getLayerMap() {
  return _layerMap;
}

void Texture::bindTexture() {
  glBindTexture(GL_TEXTURE_2D_ARRAY, _ID);
}

void Texture::unbindTexture() {
  glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
}

void Texture::deleteTexture() {
  glDeleteTextures(1, &_ID);
}