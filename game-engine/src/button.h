#ifndef BUTTON_H
#define BUTTON_H

#include <glm/glm.hpp>

#include "ui.h"
#include "texture.h"
#include "shader.h"


class Button : public UI {
public:
    Button(glm::vec3 colour, glm::vec2 position, glm::vec2 size);
    ~Button();

    void draw(Shader &shader, Texture2D &texture);
    void init_data() override;
   
    bool is_mouse_inside(float xpos, float ypos);
    // maybe create some kind of onMouseEnter function (or adjacent)
    
private:
    glm::vec3 colour;
    glm::vec2 position;
    glm::vec2 size;

    bool mouse_inside = false;

    void print_button_dimensions();
};

#endif
