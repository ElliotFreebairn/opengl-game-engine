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
    glm::vec2 position(screenWidth / 3.0f, screenHeight / 1.3f);
    glm::vec2 size(screenWidth / 4, screenHeight / 10.0f);
    glm::vec4 colour(0.5f, 0.5f, 0.5f, 1.0f);

    Button button(colour, position, size);
    button.set_visibility(true);
    buttons.push_front(button);
}

void UIManager::ProcessInput(GLFWwindow *window)
{
    if (keys[GLFW_KEY_SPACE])
    {
        active = !active;
        keys[GLFW_KEY_SPACE] = false;
    }
    if (keys[GLFW_KEY_ENTER])
    {
        draggable = !draggable;
    }

    if (active)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    } else {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
}

UIManager::~UIManager() = default;

void UIManager::Update(float deltaTime, float xpos, float ypos, Game &game) {
    // loop through UI elements, get the UI object which mouse is inside
    for (Button &btn : buttons)
    {
        if (btn.is_visible() && btn.is_clicked(xpos, ypos, keys) && !btn.is_draggable())
        {
            game.spawn_block("rectangle", "block", true);
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
        if(btn.is_visible()) btn.draw(shader, texture);
    }
}

bool UIManager::is_active()
{
    return active;
}

