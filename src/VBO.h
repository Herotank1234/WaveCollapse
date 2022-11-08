#ifndef VBO_H
#define VBO_H

#include "../lib/glad/include/glad/glad.h"

class VBO {
public:
  VBO(GLfloat* vertices, GLsizeiptr size);
  void bindBuffer();
  void unbindBuffer();
  void deleteBuffer();
private:
  GLuint _ID;
};

#endif