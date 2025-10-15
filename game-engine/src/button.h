#ifndef BUTTON_H
#define BUTTON_H

#include <glm/glm.hpp>

#include "ui.h"
#include "texture.h"
#include "shader.h"


class Button : public UI {
public:
    Button();
    ~Button();

    void draw(Shader &shader, Texture2D &texture, glm::vec2 position, glm::vec2 size, glm::vec3 colour);
private:
    void init_data() override;
};

#endif