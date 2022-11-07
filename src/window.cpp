#include "window.h"
#include <iostream>

const int TILE_SIZE = 14;
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
" gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
" FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";


Window::Window(Board* board) : _board(board) {}

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
  glViewport(0, 0, 800, 800);
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  glfwSwapBuffers(_window);
  return 0;
}

Window::~Window() {
  if(_window != NULL) {
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