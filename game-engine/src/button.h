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
    
    void set_visibility(bool visible);

    // getters
    bool is_draggable();
    bool is_visible();
private:
    bool visible = false;
    bool draggable = false;
};
#endif
