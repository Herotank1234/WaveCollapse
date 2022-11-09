#ifndef STRUCTS_H
#define STRUCTS_H
#include "../lib/glad/include/glad/glad.h"

typedef struct Vertex {
  GLfloat x, y, z, tx, ty, c;
  Vertex(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat tx1, GLfloat ty1, GLfloat c1);
} Vertex;

typedef struct TriangleIndices {
  GLuint x, y, z;
  TriangleIndices(GLuint x1, GLuint y1, GLuint z1);
} TriangleIndices;

typedef struct ImageData {
  int width, height, colorChs;
  unsigned char* bytes;
} ImageData;

#endif