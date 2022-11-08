#ifndef WINDOW_H
#define WINDOW_H
#include "board.h"
#include "shader.h"
#include "EBO.h"
#include "VAO.h"
#include "VBO.h"
#include "../lib/glad/include/glad/glad.h"
#include <GLFW/glfw3.h>

class Window {
public:
  Window(Board* board);
  ~Window();
  int windowInit();
  bool shouldClose();
  void pollEvents();
  void initVertices();
  void initIndices();
  void updateDisplay();
private:
  GLFWwindow* _window;
  Board* _board;
  VBO* _VBO;
  EBO* _EBO;
  VAO* _VAO;
  Shader* _shader;
  typedef struct Vertex {
    GLfloat x, y, z;
    Vertex(GLfloat x1, GLfloat y1, GLfloat z1);
  } Vertex;
  typedef struct SquareIndices {
    GLuint x, y, z;
    SquareIndices(GLuint x1, GLuint y1, GLuint z1);
  } SquareIndices;
  std::vector<Vertex> _vertices;
  std::vector<SquareIndices> _indices;
};

#endif