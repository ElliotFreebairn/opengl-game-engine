#include "ui.h"
#include <GLFW/glfw3.h>

UI::UI(glm::vec4 colour, glm::vec2 position, glm::vec2 size)
{
    this->colour = colour;
    this->position = position;
    this->size = size;
}

bool UI::is_clicked(float xpos, float ypos, bool keys[]) {
    if (!is_inside(xpos, ypos) || !keys[GLFW_MOUSE_BUTTON_LEFT])
    {
        return false;
    }
    return true;
}

bool UI::is_inside(float xpos, float ypos) {
    float leftX = position.x;
    float rightX = position.x + size.x;
    float topY = position.y;
    float bottomY = position.y + size.y;

    if ((xpos  > leftX && xpos < rightX) &&
        (ypos > topY && ypos < bottomY))
    {
        return true;
    } 
    return false;
}

// setters
void UI::set_colour(glm::vec4 colour)
{
    this->colour = colour;
}

void UI::set_position(glm::vec2 position)
{
    this->position = position;
}

void UI::set_size(glm::vec2 size)
{
    this->size = size;
}

// getters
glm::vec4 UI::get_colour()
{
    return colour;
}

glm::vec2 UI::get_position()
{
    return position;
}

glm::vec2 UI::get_size()
{
    return size;
}
