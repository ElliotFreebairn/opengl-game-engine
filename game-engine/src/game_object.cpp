#include "game_object.h"

GameObject::GameObject()
  : Position(0.0f, 0.0f, 0.0f), Colour(1.0f), Sprite() {}

GameObject::GameObject(glm::vec3 pos, glm::vec3 colour, Texture2D sprite)
  : Position(pos), Colour(colour), Sprite(sprite) {}


