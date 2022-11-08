#include "VAO.h"

VAO::VAO() {
  glGenVertexArrays(1, &_ID);
}

void VAO::linkAttrib(VBO vbo, GLuint layout, GLuint numComponents, GLenum type,
  GLsizeiptr stride, void* offset) {
  vbo.bindBuffer();
  glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
  glEnableVertexAttribArray(layout);
  vbo.unbindBuffer();
}

void VAO::bindArray() {
  glBindVertexArray(_ID);
}

void VAO::unbindArray() {
  glBindVertexArray(0);
}

void VAO::deleteArray() {
  glDeleteVertexArrays(1, &_ID);
}