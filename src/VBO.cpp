#include "./VBO.h"

VBO::VBO(GLfloat* vertices, GLsizeiptr size) {
  glGenBuffers(1, &_ID);
  glBindBuffer(GL_ARRAY_BUFFER, _ID);
  glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void VBO::bindBuffer() {
  glBindBuffer(GL_ARRAY_BUFFER, _ID);
}

void VBO::unbindBuffer() {
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::deleteBuffer() {
  glDeleteBuffers(1, &_ID);
}