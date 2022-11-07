#ifndef WINDOW_H
#define WINDOW_H
#include "board.h"
#include "../lib/glad/include/glad/glad.h"
#include <GLFW/glfw3.h>

class Window {
public:
  Window(Board* board);
  ~Window();
  int windowInit();
  bool shouldClose();
  void pollEvents();
private:
  GLFWwindow* _window;
  Board* _board;
};

#endif