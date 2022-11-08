#include "texture.h"

Texture::Texture() {
  glGenTextures(1, &_ID);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, _ID);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

void Texture::changeTexture(ImageData* imgData) {
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgData->width, imgData->height,
    0, GL_RGB, GL_UNSIGNED_BYTE, imgData->bytes);
  glGenerateMipmap(GL_TEXTURE_2D);
}

void Texture::bindTexture() {
  glBindTexture(GL_TEXTURE_2D, _ID);
}

void Texture::unbindTexture() {
  glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::deleteTexture() {
  glDeleteTextures(1, &_ID);
}