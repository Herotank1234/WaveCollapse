#include "window.h"
#include <iostream>
#include <math.h>

const int TILE_SIZE = 14;
const int POINTS_PER_TILE = 12;
const int WINDOW_SIZE = 2;
const float WINDOW_H_START = -1.0f;
const float WINDOW_V_START = 1.0f;

Window::Window(Board* board) : _board(board) {
  std::pair<int, int> size = _board->getSize();
  _vertices = new GLfloat[POINTS_PER_TILE * size.first * size.second];
}

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

  GLfloat vertices[] = {
    -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
    0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
    0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f
  };

  glGenVertexArrays(1, &_VAO);
  glGenBuffers(1, &_VBO);

  glBindVertexArray(_VAO);
  glBindBuffer(GL_ARRAY_BUFFER, _VBO);

  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  glfwSwapBuffers(_window);
  return 0;
}

Window::~Window() {
  delete [] _vertices;
  if(_window != NULL) {
    glDeleteVertexArrays(1, &_VAO);
    glDeleteBuffers(1, &_VBO);
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

void Window::initVertices() {
  std::pair<int, int> size = _board->getSize();
  float stepSizeH = WINDOW_SIZE / (float) size.first, stepSizeV = WINDOW_SIZE / (float) size.second;
  for(int i = 0; i < size.second; i++) {
    for(int j = 0; j < size.first; j++) {
      int index = (i * POINTS_PER_TILE * size.second) + (j * POINTS_PER_TILE);
      _vertices[index] = WINDOW_H_START + (j * stepSizeH); 
      _vertices[index + 1] = WINDOW_V_START - (i * stepSizeV); 
      _vertices[index + 2] = 0.0f; 
      _vertices[index + 3] = WINDOW_H_START + ((j + 1) * stepSizeH); 
      _vertices[index + 4] = WINDOW_V_START - (i * stepSizeV); 
      _vertices[index + 5] = 0.0f; 
      _vertices[index + 6] = WINDOW_H_START + (j * stepSizeH); 
      _vertices[index + 7] = WINDOW_V_START - ((i + 1) * stepSizeV); 
      _vertices[index + 8] = 0.0f;
      _vertices[index + 9] = WINDOW_H_START + ((j + 1) * stepSizeH); 
      _vertices[index + 10] = WINDOW_V_START - ((i + 1) * stepSizeV);
      _vertices[index + 11] = 0.0f; 
    }
  }
}

void Window::updateDisplay() {
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  _shader->activateProgram();
  glBindVertexArray(_VAO);
  glDrawArrays(GL_TRIANGLES, 0, 3);
  glfwSwapBuffers(_window);
}