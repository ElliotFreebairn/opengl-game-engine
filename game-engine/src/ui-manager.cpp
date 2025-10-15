#include "ui-manager.h"
#include "button.h"
#include "resource_manager.h"
#include <glm/gtc/matrix_transform.hpp>


UIManager::UIManager(const int width, const int height) {
    screenWidth = width;
    screenHeight = height;
    ResourceManager::LoadShader("shaders/vertex_ui.vs", "shaders/fragment_ui.fs", "ui");
}

UIManager::~UIManager() = default;

void UIManager::Update(float deltaTime) {
    // Implement update logic for UI elements based on deltaTime

}

void UIManager::Render() {
    glm::mat4 proj = glm::ortho(0.0f, static_cast<float>(screenWidth),
                                static_cast<float>(screenHeight), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("ui").Use().SetInteger("image", 0);
    ResourceManager::GetShader("ui").SetMatrix4("projection", proj);
    Button button;
    Shader shader = ResourceManager::GetShader("ui");
    Texture2D texture;

    glm::vec2 position(0.0f, screenHeight * 2.0f / 3.0f);
    glm::vec2 size(screenWidth, screenHeight / 3.0f);
    glm::vec3 color(0.0f, 0.0f, 1.0f);

    button.draw(shader, texture, position, size, color);
}