#include "game.h"
#include "resource_manager.h"
#include "shader.h"
#include "player.h"
#include "block.h"
#include "level.h"

#include "map_utils.h"

#include <vector>

#include <glm/glm.hpp>

// Game-related data
Player *player;
glm::vec3 shooting_velocity(0.0f);
bool wireframe_active = false;

// Blocks
//Block *bullet_block;

std::vector<Block> shooting_blocks;
float last_block_place = 0.0f;
float last_block_damage = 0.0f;

// helper methods
BlockType texture_to_block_type(const std::string& texture_name)
{
    if (texture_name == "dirt_block")
        return BlockType::Dirt;
    if (texture_name == "cobblestone_block")
        return BlockType::Cobblestone;
    if (texture_name == "oak_block")
        return BlockType::Oak;

    return BlockType::Air;
}

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

    has_target_block = find_target_block(target_block_cell);
    //bullet_block->Position += shooting_velocity * deltaTime;
}

void Game::Render()
{    
    if (wireframe_active) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
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



    level.draw();

    for (Block &block : shooting_blocks)
    {
        block.draw();
    }

    if (has_target_block) {
        draw_block_outline(target_block_cell);
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

            spawn_block(texture_name, false);
            last_block_place = glfwGetTime();
        }
    }
    if (keys[GLFW_KEY_K])
        level.save_map("minecraft");
    if (keys[GLFW_KEY_L])
        level.load_map("minecraft");
    if (keys[GLFW_KEY_R]) {
        wireframe_active = !wireframe_active;
        keys[GLFW_KEY_R] = false;
    }
    if (keys[GLFW_KEY_G]) {
        if (has_target_block && glfwGetTime() - last_block_damage > 0.2f) {
            level.damage_block(target_block_cell.x, target_block_cell.y, target_block_cell.z);
            last_block_damage = glfwGetTime();
        }
    }
}

void Game::ProcessMouseInput(float xoffset, float yoffset)
{
    player->get_camera().ProcessMouseMovement(xoffset, yoffset);
}

void Game::spawn_block(std::string texture_name, bool shooting_block)
{
    glm::vec3 target = player->get_camera().Position +
        glm::normalize(player->get_camera().Front) * 3.0f;

    glm::ivec3 cell = world_to_grid(target);  

    // ensure cell is in bounds
    if (!level.in_bounds(cell.x, cell.y, cell.z)) {
        std::cout << "cell is out of bounds" << std::endl;
        return;
    }

    // only place block if the cell is an air block
    if (level.is_air(cell.x, cell.y, cell.z)) {
        BlockCell block_cell;
        block_cell.type = texture_to_block_type(texture_name);
        block_cell.health = 10;

        level.set_block(cell.x, cell.y, cell.z, block_cell);
        std::cout << "block has been set" << std::endl;
    }
}

void Game::outline_block(std::string texture_name) {
    glm::vec3 target = player->get_camera().Position +
        glm::normalize(player->get_camera().Front) * 3.0f;

    glm::ivec3 cell = world_to_grid(target);

    if (!level.in_bounds(cell.x, cell.y, cell.z)) {
        std::cout << "cell is out of bounds" << std::endl;
        return;
    }
}

bool Game::find_target_block(glm::ivec3& hit_cell) const
{
    glm::vec3 origin = player->get_camera().Position;
    glm::vec3 dir = glm::normalize(player->get_camera().Front);

    for (float t = 3.0f; t < 4.5f; t+= 0.05f){
        glm::vec3 p = origin + dir * t;
        glm::ivec3 cell = world_to_grid(p);

        if (!level.in_bounds(cell.x, cell.y, cell.z)) {
            continue;
        }
        
        hit_cell = cell;
        return true;
        //if (!level.is_air(cell.x, cell.y, cell.z)) {
        //    hit_cell = cell;
        //    return true;
        //}
    }

    return false;
}

void Game::draw_block_outline(const glm::ivec3& cell)
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    Block outline_block("rectangle", "dirt_block", glm::vec3(cell.x, cell.y, cell.z));
    outline_block.Size = glm::vec3(1.02f, 1.02f, 1.02f);
    outline_block.draw();

    glPolygonMode(GL_FRONT_AND_BACK, wireframe_active ? GL_LINE : GL_FILL);
}
