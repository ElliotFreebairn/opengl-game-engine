#include "button.h"
#include "resource_manager.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>


Button::Button(glm::vec4 colour, glm::vec2 position, glm::vec2 size) {
    this->colour = colour;
    this->position = position;
    this->size = size;
    init_data();
}

Button::~Button() = default;

bool Button::is_clicked(float xpos, float ypos, bool keys[]) {
    if (!is_inside(xpos, ypos) || !keys[GLFW_MOUSE_BUTTON_LEFT])
    {
        set_colour(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));
        return false;
    }
    set_colour(glm::vec4(0.5f, 0.5f, 0.5f, 0.2f));
    return true;
}

bool Button::is_inside(float xpos, float ypos) {
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

void Button::draw(Shader &shader, Texture2D &texture) {
    shader.Use();
    glm::mat4 model = glm::mat4(1.0f); // creates the 4 x 4 identity matrix
    model = glm::translate(model, glm::vec3(position, 0.0f));
    model = glm::scale(model, glm::vec3(size, 1.0f));

    shader.SetMatrix4("model", model);
    shader.SetVector4f("spriteColor", colour);

    glActiveTexture(GL_TEXTURE0);
    texture.Bind();

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void Button::init_data() {
    unsigned int VBO;

    float vertices [] = {
        // pos      // tex
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

    // texture coordinates
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Button::set_colour(glm::vec4 colour)
{
    this->colour = colour;
}

bool Button::is_visible()
{
    return visible;
}

void Button::set_visibility(bool visible)
{
    this->visible = visible;
}
