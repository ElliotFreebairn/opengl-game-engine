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

    glm::vec3 colour;
    glm::vec2 position;
    glm::vec2 size;
};

#endif
