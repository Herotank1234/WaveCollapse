#include "window.h"
#include <iostream>
#include <math.h>

const int TILE_SIZE = 14;
const int POINTS_PER_TILE = 12;
const int WINDOW_SIZE = 2;
const float WINDOW_H_START = -1.0f;
const float WINDOW_V_START = 1.0f;

Window::Window(Board* board) : _board(board) {}

Window::Vertex::Vertex(GLfloat x1, GLfloat y1, GLfloat z1) : x(x1), y(y1), z(z1) {}

Window::SquareIndices::SquareIndices(GLuint x1, GLuint y1, GLuint z1) : x(x1), y(y1), z(z1) {}

int Window::windowInit() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  std::pair<int, int> size = _board->getSize();
  _window = glfwCreateWindow(size.first * TILE_SIZE, size.second * TILE_SIZE, "hello", NULL, NULL);
  if(_window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(_window);
  gladLoadGL();
  glViewport(0, 0, size.first * TILE_SIZE, size.second * TILE_SIZE);

  _shader = new Shader("./src/shaders/default.vert", "./src/shaders/default.frag");

  initVertices();
  initIndices();

  _VAO = new VAO();
  _VAO->bindArray();

  _VBO = new VBO((GLfloat *) &_vertices.front(), _vertices.size() * sizeof(Vertex));
  _EBO = new EBO((GLuint *) &_indices.front(), _indices.size() * sizeof(SquareIndices));
  
  _VAO->linkVBO(*_VBO, 0);
  
  _VAO->unbindArray();
  _VBO->unbindBuffer();
  _EBO->unbindBuffer();

  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  glfwSwapBuffers(_window);
  return 0;
}

Window::~Window() {
  if(_window != NULL) {
    _VAO->deleteArray();
    _VBO->deleteBuffer();
    _EBO->deleteBuffer();
    _shader->deleteProgram();
    glfwDestroyWindow(_window);
    glfwTerminate();
  }
}

bool Window::shouldClose() {
  return glfwWindowShouldClose(_window);
}

void Window::pollEvents() {
  glfwPollEvents();
}

void Window::updateDisplay() {
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  _shader->activateProgram();
  _VAO->bindArray();
  for(size_t i = 0; i < _indices.size(); i+=2) {
    _EBO->bindBuffer();
    _EBO->changeBufferData((GLuint *)&_indices[i], 2 * sizeof(SquareIndices)); 
    glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, 0);
  }
  glfwSwapBuffers(_window);
}

void Window::initVertices() {
  std::pair<int, int> size = _board->getSize();
  float stepSizeH = WINDOW_SIZE / (float) size.first, stepSizeV = WINDOW_SIZE / (float) size.second;
  for(int i = 0; i <= size.second; i++) {
    for(int j = 0; j <= size.first; j++) {
      _vertices.push_back(Vertex(WINDOW_H_START + (j * stepSizeH),
        WINDOW_V_START - (i * stepSizeV), 0.0f));
    }
  }
}

void Window::initIndices() {
  std::pair<int, int> size = _board->getSize();
  int length = size.first, width = size.second, adjLength = length + 1;
  for(int i = 0; i < length; i++) {
    for(int j = 0; j < width; j++) {
      _indices.push_back(SquareIndices((i + 1) * adjLength + j,
        i * adjLength + j, i * adjLength + (j + 1)));
      _indices.push_back(SquareIndices((i + 1) * adjLength + j,
        i * adjLength + (j + 1), (i + 1) * adjLength + (j + 1)));
    }
  }
}