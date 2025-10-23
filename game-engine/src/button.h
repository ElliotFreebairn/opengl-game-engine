#ifndef BUTTON_H
#define BUTTON_H

#include <glm/glm.hpp>

#include "ui.h"
#include "texture.h"
#include "shader.h"


class Button : public UI {
public:
    Button(glm::vec4 colour, glm::vec2 position, glm::vec2 size);
    ~Button();

    // core ui methods
    void draw(Shader &shader, Texture2D &texture);
    void init_data() override;
  
    // interface between ui and the button
    bool is_clicked(float xpos, float ypos, bool keys[]);
    
    // setters
    void set_colour(glm::vec4 colour);
    void set_position(glm::vec2 position);
    void set_size(glm::vec2 size);
    void set_visibility(bool visible);

    // getters
    glm::vec4 get_colour();
    glm::vec2 get_position();
    glm::vec2 get_size();
    bool is_activated();
    bool is_draggable();
    bool is_visible();


private:
    glm::vec4 colour;
    glm::vec2 position;
    glm::vec2 size;

    bool visible = false;
    bool inside = false;
    bool clicked = false;
    bool draggable = false;

    bool is_inside(float xpos, float ypos);
};
#endif
