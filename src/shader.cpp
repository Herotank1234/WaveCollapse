#include "shader.h"
#include <fstream>
#include <cerrno>
#include <iostream>

std::string getFileContents(const char* filename) {
  std::ifstream in(filename, std::ios::binary);
  if(in) {
    std::string contents;
    in.seekg(0, std::ios::end);
    contents.resize(in.tellg());
    in.seekg(0, std::ios::beg);
    in.read(&contents[0], contents.size());
    in.close();
    return(contents);
  }
  throw(errno);
}

Shader::Shader(const char* vertexSourceFile, const char* fragmentSourceFile) {
  std::string vertexFileContents = getFileContents(vertexSourceFile);
  std::string fragmentFileContents = getFileContents(fragmentSourceFile);

  const char* vertexSource = vertexFileContents.c_str();
  const char* fragmentSource = fragmentFileContents.c_str();

  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexSource, NULL);
  glCompileShader(vertexShader);

  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
  glCompileShader(fragmentShader);
  
  _ID = glCreateProgram();
  glAttachShader(_ID, vertexShader);
  glAttachShader(_ID, fragmentShader);
  glLinkProgram(_ID);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

void Shader::activateProgram() {
  glUseProgram(_ID);
}

void Shader::deleteProgram() {
  glDeleteProgram(_ID);
}

GLuint Shader::getID() {
  return _ID;
}