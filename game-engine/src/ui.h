#ifndef UI_H
#define UI_H

#include <glm/glm.hpp>
// could be an interface class

enum Point
{
    TOP_LEFT,
    TOP_MIDDLE,
    TOP_RIGHT,
    MIDDLE_LEFT,
    MIDDLE_RIGHT,
    BOTTOM_LEFT,
    BOTTOM_MIDDLE,
    BOTTOM_RIGHT,
    NONE,
};

class UI {
public:
    UI(glm::vec4 colour, glm::vec2 position, glm::vec2 size);
    UI();

    void resize_point(float xoffset, float yoffset, Point corner);

    bool is_inside(float xpos, float ypos);
    bool is_corner_clicked(float xpos, float ypos, bool keys[], int glfw_code);
    bool is_in_corner(float xpos, float ypos);
    bool is_clicked(float xpos, float ypos, bool keys[], int glfw_code);
    Point which_point(float xpos, float ypos);
    
    // setters
    void set_colour(glm::vec4 colour);
    void set_position(glm::vec2 position);
    void set_size(glm::vec2 size);

    // getters
    glm::vec4 get_colour();
    glm::vec2 get_position();
    glm::vec2 get_size();

protected:
    virtual void init_data() = 0; // same
    unsigned int VAO;

    glm::vec2 position;
    glm::vec2 size;
    glm::vec4 colour;

    bool inside = false;
    bool clicked = false;
};

#endif
