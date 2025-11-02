#include "ui.h"
#include <GLFW/glfw3.h>

#include <iostream>

UI::UI(glm::vec4 colour, glm::vec2 position, glm::vec2 size)
{
    this->colour = colour;
    this->position = position;
    this->size = size;
}

bool UI::is_clicked(float xpos, float ypos, bool keys[], int glfw_code) {
    if (!is_inside(xpos, ypos) || !keys[glfw_code])
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

bool UI::is_corner_clicked(float xpos, float ypos, bool keys[], int glfw_code, const float diameter)
{
    if (!is_in_corner(xpos, ypos) || !keys[glfw_code])
        return false;

    return true;
}

bool UI::is_in_corner(float xpos, float ypos, const float diameter)
{
    Corner corner = which_corner(xpos, ypos, diameter);
    if (corner == Corner::NONE)
        return false;
    return true;
}

Corner UI::which_corner(float xpos, float ypos, const float diameter)
{
    float leftX = position.x, rightX = position.x + size.x;
    float topY = position.y, bottomY = position.y + size.y;
    
    if ((xpos > leftX && xpos < leftX + diameter)
        && (ypos > topY && ypos < topY + diameter))
    {
        return Corner::TOP_LEFT; 
    }
    // top right corner
    if((xpos < rightX && xpos > rightX - diameter)
       && (ypos > topY && ypos < topY + diameter))
    {
        return Corner::TOP_RIGHT;
    }
    // bottom left corner
    if ((xpos > leftX && xpos < leftX + diameter)
        && (ypos < bottomY && ypos > bottomY - diameter))
    {
        return Corner::BOTTOM_LEFT;
    }
    // bottom right corner
    if ((xpos < rightX && xpos > rightX - diameter)
        && (ypos < bottomY && ypos > bottomY - diameter))
    {
        return Corner::BOTTOM_RIGHT;
    }
    return Corner::NONE;
}

void UI::resize_corner(float xoffset, float yoffset, Corner corner)
{
    std::cout << "xoffset " << xoffset << " yoffset " << yoffset << std::endl;
    glm::vec2 current_position = get_position();
    glm::vec2 current_size = get_size();

    switch(corner)
    {
        case TOP_LEFT:
            if (xoffset < 0 && yoffset > 0) {
                set_position(glm::vec2(current_position.x - 2, current_position.y - 2));
                set_size(glm::vec2(current_size.x + 2, current_size.y + 2));
            }
            //std::cout << "TOP LEFT" << std::endl;
            break;

        case TOP_RIGHT:
            if (xoffset > 0 && yoffset > 0) {
                set_position(glm::vec2(current_position.x, current_position.y - 2));
                set_size(glm::vec2(current_size.x + 2, current_size.y + 2));
            }
            //std::cout << "TOP RIGHT" << std::endl;
            break;

        case BOTTOM_LEFT:
            if (xoffset < 0 && yoffset < 0) {
                set_position(glm::vec2(current_position.x - 2, current_position.y));
                set_size(glm::vec2(current_size.x + 2, current_size.y + 2));
            }
            //std::cout << "BOTTOM LEFT" << std::endl;
            break;

        case BOTTOM_RIGHT:
            if (xoffset > 0 && yoffset < 0) {
                set_position(glm::vec2(current_position.x, current_position.y));
                set_size(glm::vec2(current_size.x + 2, current_size.y + 2));
            }
            //std::cout << "BOTTOM RIGHT"  << std::endl;
            break;
    }
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
