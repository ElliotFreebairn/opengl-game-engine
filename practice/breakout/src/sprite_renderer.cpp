#include "sprite_renderer.h"


SpriteRenderer::SpriteRenderer(Shader &shader)
{
  this->shader = shader;
  this->initRenderData();
}

SpriteRenderer::~SpriteRenderer()
{
  glDeleteVertexArrays(1, &this->quadVAO);
}

void SpriteRenderer::initRenderData()
{
  // configure VAO/VBO
  unsigned int VBO;
  float vertices[] = { // Set of vertices at top left corner (0, 0)
    // pos      // tex
    0.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f,

    0.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 0.0f,
  };

  // Send vertices to GPU and confiure vertex attributes
  glGenVertexArrays(1, &this->quadVAO);
  glGenBuffers(1, &VBO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindVertexArray(this->quadVAO);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float),
                        (void*)0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void SpriteRenderer::DrawSprite(Texture2D &texture, glm::vec2 position,
                                glm::vec2 size, float rotate, glm::vec3 color)
{
  // prep transformations
  this->shader.Use();
  glm::mat4 model = glm::mat4(1.0f);
  // first translate (transformations are : scale happen first, then rotation, and then final 
  // translation happens; reversed order)
  model = glm::translate(model, glm::vec3(position, 0.0f));

  // translate to center of the sprite to the rotate
  model = glm::translate(model, glm::vec3(0.5 * size.x, 0.5 * size.y, 0.0));
  model = glm::rotate(model, glm::radians(rotate),
                      glm::vec3(0.0f, 0.0f, 1.0f));
  // translate back to top left (0,0) after rotating
  model = glm::translate(model, glm::vec3(-0.5 * size.x, -0.5 * size.y, 0.0));

  model = glm::scale(model, glm::vec3(size, 1.0f)); // last scale

  shader.SetMatrix4("model", model);
  shader.SetVector3f("spriteColor", color);

  glActiveTexture(GL_TEXTURE0);
  texture.Bind();

  glBindVertexArray(this->quadVAO);
  glDrawArrays(GL_TRIANGLES, 0, 6);
  glBindVertexArray(0);
}
