#ifndef VAO_H
#define VAO_H
#include "VBO.h"
#include "../lib/glad/include/glad/glad.h"

class VAO {
public:
  VAO();
  void linkAttrib(VBO vbo, GLuint layout, GLuint numComponents,
    GLenum type, GLsizeiptr stride, void* offset);
  void bindArray();
  void unbindArray();
  void deleteArray();
private:
  GLuint _ID;
};

#endif