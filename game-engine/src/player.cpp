#include "player.h"


Player::Player()
{
    set_position(0.0f, 0.0f, 0.0f);
    camera = *new Camera(get_position());
}

void Player::set_position(float x, float y, float z)
{
    camera.Position = glm::vec3(x, y, z);
}

Camera& Player::get_camera()
{
    return camera;
}

glm::vec3 Player::get_position()
{
    return camera.Position;
}

