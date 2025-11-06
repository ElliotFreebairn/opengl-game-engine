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
}

void UIManager::ProcessInput(GLFWwindow *window)
{
    bool change_cursor_type = false;
    if (keys[GLFW_KEY_M])
    {
        active = !active;
        keys[GLFW_KEY_M] = false;
    }
    if (keys[GLFW_KEY_ENTER])
    {
        resize = !resize;
        change_cursor_type = true;
        keys[GLFW_KEY_ENTER] = false;
    }

    if (active)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    } else {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

    if (change_cursor_type)
    {
        update_cursor(window);
    }
}

void UIManager::ProcessMouseInput(float xoffset, float yoffset)
{
    if (dragged_obj != nullptr)
    {
        glm::vec2 new_pos(dragged_obj->get_position().x + xoffset, dragged_obj->get_position().y - yoffset);
        dragged_obj->set_position(new_pos);
    }
    if (resized_obj != nullptr)
    {
        Point point = std::get<1>(resize_point);
        resized_obj->resize_point(xoffset, yoffset, point);
    }
}

UIManager::~UIManager() = default;

void UIManager::Update(GLFWwindow* window, float deltaTime, float xpos, float ypos, Game &game) {
    // loop through UI elements, get the UI object which mouse is inside
    for (Button &btn : buttons)
    {
        if (!btn.is_visible()) continue;
        
        if (btn.is_corner_clicked(xpos, ypos, keys, (int)GLFW_MOUSE_BUTTON_LEFT) && resize)
        {
            resized_obj = &btn;
            resize_point = std::tuple(resized_obj, btn.which_point(xpos, ypos));
            continue;
        }
        if (resize) continue;

        if (btn.is_clicked(xpos, ypos, keys, (int)GLFW_MOUSE_BUTTON_RIGHT))
        {
            dragged_obj = &btn;
            this->dragging=true;
        } else if (btn.is_clicked(xpos, ypos, keys, (int)GLFW_MOUSE_BUTTON_LEFT))
        {
            game.spawn_block("rectangle", "block", true);
            btn.set_colour(glm::vec4(0.5f, 0.5f, 0.5f, 0.6f));
        } else {
            btn.set_colour(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));
        }
    }

    if (dragged_obj && !dragged_obj->is_clicked(xpos, ypos, keys, (int)GLFW_MOUSE_BUTTON_RIGHT))
    {
        dragged_obj = nullptr;
        this->dragging=false;
    }
    if (resized_obj && !resized_obj->is_corner_clicked(xpos, ypos, keys, (int)GLFW_MOUSE_BUTTON_LEFT))
    {
        resized_obj = nullptr;
    }
    
    // defintely not the best way, but good for now
    update_cursor(window);
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

void UIManager::update_cursor(GLFWwindow* window)
{
    if (resize)
    {
        ResizeType resize_type = get_resize_type(std::get<1>(resize_point));
        switch(resize_type)
        {
            case HORIZONTAL:
                set_cursor(window, GLFW_HRESIZE_CURSOR);
                break;
            case VERTICAL:
                set_cursor(window, GLFW_VRESIZE_CURSOR);
                break;
            default:
                set_cursor(window, GLFW_HAND_CURSOR);
        }
    }
    else if (dragging)
    {
        set_cursor(window, GLFW_HAND_CURSOR);
    }
    else
    {
        set_cursor(window, GLFW_ARROW_CURSOR);
    }
}

void UIManager::set_cursor(GLFWwindow* window, int cursor_shape) {
    GLFWcursor* cursor = glfwCreateStandardCursor(cursor_shape);
    glfwSetCursor(window, cursor);
}


ResizeType UIManager::get_resize_type(Point point) {
    if (point == Point::MIDDLE_LEFT || point == Point::MIDDLE_RIGHT)
    {
        return ResizeType::HORIZONTAL;
    } 
    else if (point == Point::TOP_MIDDLE || point == Point::BOTTOM_MIDDLE)
    {
        return ResizeType::VERTICAL;
    } else {
        return ResizeType::DIAGONAL;
    }
}
