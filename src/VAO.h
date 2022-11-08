#ifndef VAO_H
#define VAO_H
#include "VBO.h"
#include "../lib/glad/include/glad/glad.h"

class VAO {
public:
  VAO();
  void linkVBO(VBO vbo, GLuint layout);
  void bindArray();
  void unbindArray();
  void deleteArray();
private:
  GLuint _ID;
};

#endif