#ifndef GAME_OBJECT
#define GAME_OBJECT

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "texture.h"

#include <string>

// Should encapsulate the variables assoicated with a basic game object, and then functions needed
class GameObject {

public:
    glm::vec3 Position;
    glm::vec3 Colour;

    Texture2D Sprite;
    
    GameObject();
    GameObject(glm::vec3 Pos, glm::vec3 Colour, Texture2D Sprite);

    void set_position(glm::vec3 position) { Position = position; }
    
    std::string position_to_str();
};
#endif
