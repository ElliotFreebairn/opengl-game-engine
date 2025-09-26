#include "game.h"
#include "resource_manager.h"
#include "shader.h"
#include "player.h"

// Game-related data
Player *player;

Game::Game()
    : keys(), width(800), height(600)
{
}

Game::Game(unsigned int width, unsigned int height)
    : keys(), width(width), height(height)
{
}

Game::~Game()
{
    delete player;
}

void Game::Init()
{
    // load shaders
    ResourceManager::LoadShader("shaders/vertex.vs", "shaders/fragment.fs", "rectangle");
    ResourceManager::LoadTexture("resources/textures/block.jpg", true, "block");

    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->width),
                                      static_cast<float>(this->height), 0.0f, -1.0f, 1.0f);


    // Initialize player
    player = new Player();
}

void Game::Update(float deltaTime)
{
    // Update game state
}

void Game::Render()
{
    // Render game objects
    // Shader shader = ResourceManager::GetShader("rectangle");
    // shader.Use();

    // glm::mat4 projection;
    // projection = glm::perspective(glm::radians(player->get_camera().Zoom), (float)this->width / (float)this->height, 0.1f, 100.0f);
    // shader.SetMatrix4("projection", projection);
    // glm::mat4 view = player->get_camera().GetViewMatrix();
    // shader.SetMatrix4("view", view);
    // Draw calls would go here
}

void Game::ProcessInput(float dt)
{
    float velocity = 500.0f;
    if (keys[GLFW_KEY_W])
        player->get_camera().ProcessKeyboard(FORWARD, dt);
    if (keys[GLFW_KEY_S])
        player->get_camera().ProcessKeyboard(BACKWARD, dt);
    if (keys[GLFW_KEY_A])
        player->get_camera().ProcessKeyboard(LEFT, dt);
    if (keys[GLFW_KEY_D])
        player->get_camera().ProcessKeyboard(RIGHT, dt);
}

void Game::ProcessMouseInput(float xoffset, float yoffset)
{
    player->get_camera().ProcessMouseMovement(xoffset, yoffset);
}