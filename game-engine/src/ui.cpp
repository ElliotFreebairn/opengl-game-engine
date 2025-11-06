#include "ui.h"
#include <GLFW/glfw3.h>

#include <iostream>

const float RADIUS = 50;
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

bool UI::is_corner_clicked(float xpos, float ypos, bool keys[], int glfw_code) 
{
    if (!is_in_corner(xpos, ypos) || !keys[glfw_code])
        return false;

    return true;
}

bool UI::is_in_corner(float xpos, float ypos)
{
    Point corner = which_point(xpos, ypos);
    if (corner == Point::NONE)
        return false;
    return true;
}

Point UI::which_point(float xpos, float ypos)
{
    // could have corners be a struct or enum with method?
    const float DIV = 4;

    float leftX = position.x;
    float rightX = position.x + size.x;
    float middleX = position.x + (size.x / 2);

    float topY = position.y;
    float bottomY = position.y + size.y;
    float middleY = position.y + (size.y / 2);

    float xoffset = size.x / DIV;
    float yoffset = size.y / DIV;
    
    //std::cout << "xoffset " << xoffset << " yoffset " << yoffset << std::endl;
    //std::cout << "middlex " << middleX << " middleY " << middleY << std::endl;

    // CORNERS
    // top left corner
    if ((xpos > leftX && xpos < leftX + xoffset) &&
        (ypos > topY && ypos < topY + yoffset))
    {
        return Point::TOP_LEFT;
    }

    // top right corner
    if ((xpos > middleX + xoffset && xpos < rightX) &&
        (ypos > topY && ypos < topY + yoffset))
    {
        return Point::TOP_RIGHT;
    }

    // bottom left corner
    if ((xpos > leftX && xpos < leftX + xoffset) &&
        (ypos > middleY + yoffset && ypos < bottomY))
    {
        return Point::BOTTOM_LEFT;
    }

    // bottom right corner
    if ((xpos > middleX + xoffset && xpos < rightX) &&
        (ypos > middleY + yoffset && ypos < bottomY))
    {
        return Point::BOTTOM_RIGHT;
    }

    // VERTICAL/HORIZONTAL
    // top middle
    if ((xpos > leftX + xoffset && xpos < rightX - xoffset) &&
        (ypos > topY && ypos < topY + yoffset))
    {
        return Point::TOP_MIDDLE;
    }

    // bottom middle
    if ((xpos > leftX + xoffset && xpos < rightX - xoffset) &&
        (ypos > middleY + yoffset && ypos < bottomY))
    {
        return Point::BOTTOM_MIDDLE;
    }

    // middle left
    if ((xpos > leftX && xpos < leftX + xoffset) &&
        (ypos > topY + yoffset && ypos < bottomY - yoffset))
    {
        return Point::MIDDLE_LEFT;
    }

    // middle right
    if ((xpos > middleX + xoffset && xpos < rightX) &&
        (ypos > topY + yoffset && ypos < bottomY - yoffset))
    {
        return Point::MIDDLE_RIGHT;
    }

    return Point::NONE;
}


void UI::resize_point(float xoffset, float yoffset, Point corner)
{
    glm::vec2 current_position = get_position();
    glm::vec2 current_size = get_size();

    const float OFFSET = 2;
    switch(corner)
    {
        case TOP_LEFT:
            if (xoffset < 0 && yoffset > 0) {
                set_position(glm::vec2(current_position.x - OFFSET, current_position.y - OFFSET));
                set_size(glm::vec2(current_size.x + OFFSET, current_size.y + OFFSET));
            }

            if (xoffset > 0 && yoffset < 0) {
                set_position(glm::vec2(current_position.x + OFFSET, current_position.y + OFFSET));
                set_size(glm::vec2(current_size.x - OFFSET, current_size.y - OFFSET));
            }
            //std::cout << "TOP LEFT" << std::endl;
            break;

        case TOP_RIGHT:
            if (xoffset > 0 && yoffset > 0) {
                set_position(glm::vec2(current_position.x, current_position.y - OFFSET));
                set_size(glm::vec2(current_size.x + OFFSET, current_size.y + OFFSET));
            }

            if (xoffset < 0 && yoffset < 0) {
                set_position(glm::vec2(current_position.x, current_position.y + OFFSET));
                set_size(glm::vec2(current_size.x - OFFSET, current_size.y - OFFSET));
            }
            break;
            //std::cout << "TOP RIGHT" << std::endl;
        case BOTTOM_LEFT:
            if (xoffset < 0 && yoffset < 0) {
                set_position(glm::vec2(current_position.x - OFFSET, current_position.y));
                set_size(glm::vec2(current_size.x + OFFSET, current_size.y + OFFSET));
            }

            if (xoffset > 0 && yoffset > 0) {
                set_position(glm::vec2(current_position.x + OFFSET, current_position.y));
                set_size(glm::vec2(current_size.x - OFFSET, current_size.y - OFFSET));
            }
            //std::cout << "BOTTOM LEFT" << std::endl;
            break;
        case BOTTOM_RIGHT:
            if (xoffset > 0 && yoffset < 0) {
                set_position(glm::vec2(current_position.x, current_position.y));
                set_size(glm::vec2(current_size.x + OFFSET, current_size.y + OFFSET));
            }

            if (xoffset < 0 && yoffset > 0) {
                set_position(glm::vec2(current_position.x, current_position.y));
                set_size(glm::vec2(current_size.x - OFFSET, current_size.y - OFFSET));
            }
            //std::cout << "BOTTOM RIGHT"  << std::endl;
        case TOP_MIDDLE:
            if (yoffset > 0) {
                set_position(glm::vec2(current_position.x, current_position.y - OFFSET));
                set_size(glm::vec2(current_size.x, current_size.y + OFFSET));
            }

            if (yoffset < 0) {
                set_position(glm::vec2(current_position.x, current_position.y + OFFSET));
                set_size(glm::vec2(current_size.x, current_size.y - OFFSET));
            }
            break;
        case BOTTOM_MIDDLE:
            if (yoffset < 0) {
                set_position(glm::vec2(current_position.x, current_position.y));
                set_size(glm::vec2(current_size.x, current_size.y + OFFSET));
            }

            if (yoffset > 0) {
                set_position(glm::vec2(current_position.x, current_position.y));
                set_size(glm::vec2(current_size.x, current_size.y - OFFSET));
            }
            break;
        case MIDDLE_LEFT:
            if (xoffset < 0) {
                set_position(glm::vec2(current_position.x - OFFSET, current_position.y));
                set_size(glm::vec2(current_size.x + OFFSET, current_size.y));
            }

            if (xoffset > 0) {
                set_position(glm::vec2(current_position.x + OFFSET, current_position.y));
                set_size(glm::vec2(current_size.x - OFFSET, current_size.y));
            }
            break;
        case MIDDLE_RIGHT:
            if (xoffset > 0) {
                set_position(glm::vec2(current_position.x, current_position.y));
                set_size(glm::vec2(current_size.x + OFFSET, current_size.y));
            }

            if (xoffset < 0) {
                set_position(glm::vec2(current_position.x, current_position.y));
                set_size(glm::vec2(current_size.x - OFFSET, current_size.y));
            }
            break;
        case NONE:
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
