// What should the player be able to do:
// They have the own the camera / move
// Ability to place blocks
#ifndef PLAYER_H
#define PLAYER_H

#include "camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

#include <iostream>

class Player
{
public:
    Player();

    Camera& get_camera();
    glm::vec3 get_position();

    void set_position(float x, float y, float z);

    void process_mouse_movement(float xoffset, float yoffset);

private:
    Camera camera;
    glm::vec3 position;
};
#endif
