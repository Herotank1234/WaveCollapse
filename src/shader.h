#ifndef SHADER_H
#define SHADER_H
#include <string>
#include "../lib/glad/include/glad/glad.h"

std::string getFileContents(const char* filename);

class Shader {
public:
  Shader(const char* vertexSourceFile, const char* fragmentSourceFile);
  void activateProgram();
  void deleteProgram();
private:
  GLuint _ID;
};

#endif