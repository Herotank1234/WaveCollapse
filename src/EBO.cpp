#include "EBO.h"

EBO::EBO(GLuint* indices, GLsizeiptr size) {
  glGenBuffers(1, &_ID);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ID);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices,  GL_STATIC_DRAW);
}

void EBO::bindBuffer() {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ID);
}

void EBO::unbindBuffer() {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::changeBufferData(GLuint* indices, GLsizeiptr size) {
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

void EBO::deleteBuffer() {
  glDeleteBuffers(1, &_ID);
}