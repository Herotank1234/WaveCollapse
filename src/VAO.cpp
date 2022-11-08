#include "VAO.h"

VAO::VAO() {
  glGenVertexArrays(1, &_ID);
}

void VAO::linkVBO(VBO vbo, GLuint layout) {
  vbo.bindBuffer();
  glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0);
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