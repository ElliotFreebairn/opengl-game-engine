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

void Player::process_inputs(GLFWwindow* window, float deltaTime)
{
    // logic here with camera movement?
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);

    std::cout << "Camera Position: "
              << camera.Position.x << ", "
              << camera.Position.y << ", "
              << camera.Position.z << std::endl;
}

Camera& Player::get_camera()
{
    return camera;
}

glm::vec3 Player::get_position()
{
    return camera.Position;
}

