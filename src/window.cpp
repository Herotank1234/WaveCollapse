#define STB_IMAGE_IMPLEMENTATION
#include "window.h"
#include <iostream>
#include <math.h>
#include <stb/stb_image.h>

const int TILE_SIZE = 32;
const int POINTS_PER_TILE = 12;
const int WINDOW_SIZE = 2;
const float WINDOW_H_START = -1.0f;
const float WINDOW_V_START = 1.0f;

Window::Window(Board* board) : _board(board) {}

int Window::windowInit() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  std::pair<int, int> size = _board->getSize();
  _window = glfwCreateWindow(size.first * TILE_SIZE, size.second * TILE_SIZE, 
    "Wave Function Collapse", NULL, NULL);
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
  initImages();

  _VAO = new VAO();
  _VAO->bindArray();

  _VBO = new VBO((GLfloat *) &_vertices.front(), _vertices.size() * sizeof(Vertex));
  _EBO = new EBO((GLuint *) &_indices.front(), 
    _indices.size() * sizeof(TriangleIndices));
  
  _VAO->linkAttrib(*_VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void *) 0);
  _VAO->linkAttrib(*_VBO, 1, 3, GL_FLOAT, sizeof(Vertex), 
    (void *) (3 * sizeof(float)));
  
  _VAO->unbindArray();
  _VBO->unbindBuffer();
  _EBO->unbindBuffer();
  _texture = new Texture(_imageMap);
  _layerMap = _texture->getLayerMap();

  GLuint tex0uni = glGetUniformLocation(_shader->getID(), "tex0");
  _shader->activateProgram();
  glUniform1i(tex0uni, 0);

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
    _texture->deleteTexture();
    for(auto it = _imageMap.begin(); it != _imageMap.end(); it++) {
      stbi_image_free(it->second->bytes);
    }
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
  updateVertices();
  _shader->activateProgram();
  _VBO->bindBuffer();
  _VBO->bufferNewData((GLfloat *) &_vertices.front(), 
    _vertices.size() * sizeof(Vertex));
  _texture->bindTexture();
  _VAO->bindArray();
  glDrawElements(GL_TRIANGLES, _indices.size() * 3, GL_UNSIGNED_INT, 0);
  glfwSwapBuffers(_window);
}

void Window::initVertices() {
  std::pair<int, int> size = _board->getSize();
  float stepSizeH = WINDOW_SIZE / (float) size.first, stepSizeV 
    = WINDOW_SIZE / (float) size.second;
  for(int i = 0; i <  size.second; i++) {
    for(int j = 0; j < size.first; j++) {
      _vertices.push_back(Vertex(WINDOW_H_START + (j * stepSizeH),
        WINDOW_V_START - (i * stepSizeV), 0.0f, 0.0f, 1.0f, 0.0f));
      _vertices.push_back(Vertex(WINDOW_H_START + (j * stepSizeH),
        WINDOW_V_START - ((i + 1) * stepSizeV), 0.0f, 0.0f, 0.0f, 0.0f));
      _vertices.push_back(Vertex(WINDOW_H_START + ((j + 1) * stepSizeH),
        WINDOW_V_START - ((i + 1) * stepSizeV), 0.0f, 1.0f, 0.0f, 0.0f));
      _vertices.push_back(Vertex(WINDOW_H_START + (j * stepSizeH),
        WINDOW_V_START - (i * stepSizeV), 0.0f, 0.0f, 1.0f, 0.0f));
      _vertices.push_back(Vertex(WINDOW_H_START + ((j + 1) * stepSizeH),
        WINDOW_V_START - ((i + 1) * stepSizeV), 0.0f, 1.0f, 0.0f, 0.0f));
      _vertices.push_back(Vertex(WINDOW_H_START + ((j + 1) * stepSizeH),
        WINDOW_V_START - (i * stepSizeV), 0.0f, 1.0f, 1.0f, 0.0f));
    }
  }
}

void Window::initIndices() {
  std::pair<int, int> size = _board->getSize();
  int length = size.first, width = size.second, index = 0;
  for(int i = 0; i < length; i++) {
    for(int j = 0; j < width; j++) {
      _indices.push_back(TriangleIndices(index, index + 1, index + 2));
      index += 3;
      _indices.push_back(TriangleIndices(index, index + 1, index + 2));
      index += 3;
    }
  }
}

void Window::initImages() {
  std::vector<std::string> imageFilenames = {"Black", "Connector", "Connector90", 
    "Connector180", "Connector270", "ConnectorEdge", "ConnectorEdge90", 
    "ConnectorEdge180", "ConnectorEdge270", "DiagPipeOne", "DiagPipeOne90", 
    "DiagPipeOne180", "DiagPipeOne270", "DiagPipeTwoL", "DiagPipeTwoR", "Dot", 
    "Dot90", "Dot180", "Dot270", "DotTwoWayH", "DotTwoWayV", "Green", "PipeCrossH",
    "PipeCrossV", "PipeGreenH", "PipeGreenV", "PipeGreyH", "PipeGreyV", "PipeSwitch",
    "PipeSwitch90", "PipeSwitch180", "PipeSwitch270", "PipeT", "PipeT90", "PipeT180", 
    "PipeT270", "Blank"
  };
  for(std::string filename : imageFilenames) {
    ImageData* data = new ImageData();
    std::string path = "./images/" + filename + ".png";
    data->bytes = stbi_load(path.c_str(), &(data->width),
      &(data->height), &(data->colorChs), 0);
    if(filename != "Blank") {
      _imageMap.insert({filename, data});
    } else {
      _imageMap.insert({"", data});
    }
  }
}

void Window::setBoard(Board* board) {
  _board = board;
}

void Window::updateVertices() {
  std::pair<int, int> size = _board->getSize();
  for(int i = 0; i < size.second; i++) {
    for(int j = 0; j < size.first; j++) {
      int index = 6 * ((i * size.first) + j);
      int texLayer = _layerMap[_board->getTileName(j, i)];
      for(int k = index; k < index + 6; k++) {
        _vertices[k].c = texLayer;
      }
    }
  }
}