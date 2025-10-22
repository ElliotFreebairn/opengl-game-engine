#include "ui-manager.h"
#include "button.h"
#include "resource_manager.h"
#include <glm/gtc/matrix_transform.hpp>

#include <list>


std::list<Button> buttons;

UIManager::UIManager(const int width, const int height) {
    screenWidth = width;
    screenHeight = height;
}

UIManager::UIManager() : keys(), screenWidth(800), screenHeight(600)
{
}

void UIManager::Init() {
    ResourceManager::LoadShader("shaders/vertex_ui.vs", "shaders/fragment_ui.fs", "ui");
    glm::vec2 position(0.0f, screenHeight * 2.0f / 3.0f);
    glm::vec2 size(screenWidth, screenHeight / 3.0f);
    glm::vec3 colour(0.0f, 1.0f, 0.0f);
    Button button(colour, position, size);
    buttons.push_front(button);
}

void UIManager::ProcessInput(GLFWwindow *window)
{
    if (keys[GLFW_KEY_SPACE])
    {
        if (!active)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            keys[GLFW_KEY_SPACE] = false;
            active = true;
        } else {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            keys[GLFW_KEY_SPACE] = false;
            active = false;
        }
    }
}

UIManager::~UIManager() = default;

void UIManager::Update(float deltaTime, float xpos, float ypos, Game &game) {
    // Implement update logic for UI elements based on deltaTime
    // update should call is mouseInside in button, and maybe change a flag

    for (Button &btn : buttons)
    {
        if(btn.is_mouse_inside(xpos, ypos) && keys[GLFW_MOUSE_BUTTON_LEFT])
        {
            btn.activate();
            game.spawn_block("rectangle", "block", true);
        } else if(btn.is_mouse_inside(xpos, ypos) && !keys[GLFW_MOUSE_BUTTON_LEFT])
        {
            btn.deactivate();
        }
    }

}

void UIManager::Render() {
    glm::mat4 proj = glm::ortho(0.0f, static_cast<float>(screenWidth),
                                static_cast<float>(screenHeight), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("ui").Use().SetInteger("image", 0);
    ResourceManager::GetShader("ui").SetMatrix4("projection", proj);

    Shader shader = ResourceManager::GetShader("ui");
    Texture2D texture;


    for (Button &btn : buttons)
    {
        btn.draw(shader, texture);
    }

    // change this! button shoudn't be created every render, only draw function
    //Button button;
    //Shader shader = ResourceManager::GetShader("ui");
    //Texture2D texture;

    //button.draw(shader, texture, position, size, color);
}

bool UIManager::is_active()
{
    return active;
}

