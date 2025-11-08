#include "game.h"
#include "resource_manager.h"
#include "shader.h"
#include "player.h"
#include "block.h"

#include <vector>

#include <glm/glm.hpp>

// Game-related data
Player *player;
glm::vec3 shooting_velocity(0.0f);

// Blocks
//Block *bullet_block;

std::vector<Block> shooting_blocks;
std::vector<Block> blocks;
float last_block_place = 0.0f;

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
    ResourceManager::LoadTexture("resources/textures/dirt.jpg", true, "dirt_block");
    ResourceManager::LoadTexture("resources/textures/cobblestone.jpeg", true, "cobblestone_block");
    ResourceManager::LoadTexture("resources/textures/oak.jpg", true, "oak_block");

    // Initialize player
    player = new Player();
}

void Game::Update(float deltaTime)
{
    shooting_velocity = glm::normalize(player->get_camera().Front) * 3.0f; // 10 units per second

    // Update game state
    for (Block &block : shooting_blocks)
    {
        block.Position += shooting_velocity * deltaTime;
    }
    //bullet_block->Position += shooting_velocity * deltaTime;
}

void Game::Render()
{
    // Render game objects
    Shader shader = ResourceManager::GetShader("rectangle");
    shader.Use();

    glm::mat4 projection;
    projection = glm::perspective(glm::radians(player->get_camera().Zoom), (float)this->width / (float)this->height, 0.1f, 100.0f);
    shader.SetMatrix4("projection", projection);
    glm::mat4 view = player->get_camera().GetViewMatrix();
    shader.SetMatrix4("view", view);
    // Draw calls would go here
    // bullet_block->draw();

    for (Block &block : blocks)
    {
        block.draw();
    }

    for (Block &block : shooting_blocks)
    {
        block.draw();
    }
}

void Game::ProcessInput(float dt)
{
    if (keys[GLFW_KEY_W])
        player->get_camera().ProcessKeyboard(FORWARD, dt);
    if (keys[GLFW_KEY_S])
        player->get_camera().ProcessKeyboard(BACKWARD, dt);
    if (keys[GLFW_KEY_A])
        player->get_camera().ProcessKeyboard(LEFT, dt);
    if (keys[GLFW_KEY_D])
        player->get_camera().ProcessKeyboard(RIGHT, dt);
    if (keys[GLFW_KEY_SPACE])
        player->get_camera().ProcessKeyboard(UP, dt);
    if (keys[GLFW_KEY_LEFT_SHIFT])
        player->get_camera().ProcessKeyboard(DOWN, dt);
    if (keys[GLFW_MOUSE_BUTTON_LEFT]) {
        if (glfwGetTime() - last_block_place > 0.1f) {
            int randomNum = rand() % 3;
            
            std::string texture_name = "";
            switch (randomNum) {
                case 0:
                    texture_name = "dirt_block"; 
                    break;
                case 1:
                    texture_name = "cobblestone_block";
                    break;
                case 2:
                    texture_name = "oak_block";
                    break;
            }

            spawn_block("rectangle", texture_name);
            last_block_place = glfwGetTime();
        }
    }
}

void Game::ProcessMouseInput(float xoffset, float yoffset)
{
    player->get_camera().ProcessMouseMovement(xoffset, yoffset);
}

void Game::spawn_block(std::string shader_name, std::string texture_name, bool shooting_block)
{
	Block block(shader_name, texture_name);

	// Position a certain distance in front of the player
	glm::vec3 target = player->get_camera().Position + glm::normalize(player->get_camera().Front) * 5.0f;
	glm::vec3 block_pos = glm::floor(target);

	block.set_position(block_pos);

    if (shooting_block)
    {
        shooting_blocks.push_back(block);
    } else {
        blocks.push_back(block);
    }
}
