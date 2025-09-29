#ifndef RECTANGLE
#define RECTANGLE

#include "game_object.h"
#include "shader.h"

#include <iostream>

class Rectangle: public GameObject {
public:
  Rectangle() {};
  Rectangle(std::string shader_name, std::string texture_name);

  void init_data(std::string shader_name, std::string texture_name);

  void draw();

  Shader shader;

  unsigned int VAO;
  unsigned int VBO;
};
#endif
