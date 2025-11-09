#include "game_object.h"

GameObject::GameObject()
  : Position(0.0f, 0.0f, 0.0f), Size(1.0f, 1.0f, 1.0f), Colour(1.0f), Sprite() {}

GameObject::GameObject(glm::vec3 pos, glm::vec3 size, glm::vec3 colour, Texture2D sprite)
  : Position(pos), Size(size), Colour(colour), Sprite(sprite) {}

std::string GameObject::position_to_str()
{
    std::string line = 
        std::to_string(Position.x) + "," +
        std::to_string(Position.y) + "," +
        std::to_string(Position.z);

    return line;
}
