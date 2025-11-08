#ifndef BLOCK
#define BLOCK 

#include "game_object.h"
#include "shader.h"

#include <iostream>

class Block: public GameObject {
public:
  Block() {};
  Block(std::string shader_name, std::string texture_name);

  void init_data(std::string shader_name, std::string texture_name);

  void draw();

  Shader shader;

  unsigned int VAO;
  unsigned int VBO;
};
#endif
