#ifndef EBO_H
#define EBO_H
#include "../lib/glad/include/glad/glad.h"

class EBO {
public:
  EBO(GLuint* indices, GLsizeiptr size);
  void bindBuffer();
  void unbindBuffer();
  void changeBufferData(GLuint* indices, GLsizeiptr size);
  void deleteBuffer();
private:
  GLuint _ID;
};

#endif