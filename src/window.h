#ifndef WINDOW_H
#define WINDOW_H
#include "board.h"
#include "shader.h"
#include "EBO.h"
#include "VAO.h"
#include "VBO.h"
#include "texture.h"
#include "structs.h"
#include "../lib/glad/include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <map>

class Window {
public:
  Window(Board* board);
  ~Window();
  int windowInit();
  bool shouldClose();
  void pollEvents();
  void initVertices();
  void initIndices();
  void initImages();
  void updateDisplay();
private:
  GLFWwindow* _window;
  Board* _board;
  VBO* _VBO;
  EBO* _EBO;
  VAO* _VAO;
  Texture* _texture;
  Shader* _shader;
  std::vector<Vertex> _vertices;
  std::vector<TriangleIndices> _indices;
  std::map<std::string, ImageData*> _imageMap;
};

#endif