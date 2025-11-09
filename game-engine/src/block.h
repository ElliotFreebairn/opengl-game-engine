#ifndef BLOCK
#define BLOCK 

#include <glm/glm.hpp>

#include "game_object.h"
#include "shader.h"

#include <iostream>

class Block: public GameObject {
public:
    Block();
    Block(std::string shader_name, std::string texture_name);
    Block(std::string shader_name, std::string texture_name, glm::vec3 position);

    void init_data(std::string shader_name, std::string texture_name);
    
    std::string get_shader_name();
    std::string get_texture_name();

    void draw();

    Shader shader;
    unsigned int VAO;
    unsigned int VBO;

private:
    std::string shader_name;
    std::string texture_name;
};
#endif
