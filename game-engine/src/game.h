#ifndef GAME_H
#define GAME_H

#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "game_object.h"
#include "camera.h"
#include "level.h"
#include "side.h"


class Game
{
public:
    Game();
    Game(unsigned int width, unsigned int height);
    ~Game();
    
    Level level;
    
    bool keys[1024];
    unsigned int width, height;

    bool has_target_block;
    glm::ivec3 target_block_cell;

    // init game state (load all shaders/textures/levels)
    void Init();
    // game loop
    void ProcessInput(float dt);
    void ProcessMouseInput(float xoffset, float yoffset);
    void Update(float deltaTime);
    void Render();
    void spawn_block(std::string texture_name, bool shooting_block = false);
    void outline_block(std::string texture_name); 

    bool find_target_block(glm::ivec3& hit_cell) const;
    void draw_block_outline(const glm::ivec3& cell);

};
#endif
