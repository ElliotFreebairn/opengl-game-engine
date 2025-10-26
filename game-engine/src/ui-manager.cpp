#include "ui-manager.h"
#include "button.h"
#include "resource_manager.h"
#include <glm/gtc/matrix_transform.hpp>

#include <list>
#include <optional>


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

    // draggable object (may change soon)
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
        keys[GLFW_KEY_ENTER] = false;
    }

    if (active)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    } else {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
}

void UIManager::ProcessMouseInput(float xoffset, float yoffset)
{
    if (dragged_obj != nullptr)
    {
        glm::vec2 new_pos(dragged_obj->get_position().x + xoffset, dragged_obj->get_position().y - yoffset);
        dragged_obj->set_position(new_pos);
    }
}

UIManager::~UIManager() = default;

void UIManager::Update(float deltaTime, float xpos, float ypos, Game &game) {
    // loop through UI elements, get the UI object which mouse is inside
    for (Button &btn : buttons)
    {
        if (!btn.is_visible()) continue;

        if (btn.is_clicked(xpos, ypos, keys))
        {
            if (draggable)
            {
                dragged_obj = &btn;
            } else {
                game.spawn_block("rectangle", "block", true);
                btn.set_colour(glm::vec4(0.5f, 0.5f, 0.5f, 0.6f));
            }
        } else {
            btn.set_colour(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));
        }
    }

    if (draggable && dragged_obj && !dragged_obj->is_clicked(xpos, ypos, keys))
    {
        dragged_obj = nullptr;
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

