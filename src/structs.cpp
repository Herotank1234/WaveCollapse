#include "structs.h"

Vertex::Vertex(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat tx1, GLfloat ty1) 
  : x(x1), y(y1), z(z1), tx(tx1), ty(ty1) {}

TriangleIndices::TriangleIndices(GLuint x1, GLuint y1, GLuint z1) 
  : x(x1), y(y1), z(z1) {}