#ifndef GAME_H
#define GAME_H

#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "game_object.h"
#include "camera.h"
#include "level.h"

class Game
{
public:
    Game();
    Game(unsigned int width, unsigned int height);
    ~Game();
    
    Level level;
    
    bool keys[1024];
    unsigned int width, height;

    // init game state (load all shaders/textures/levels)
    void Init();
    // game loop
    void ProcessInput(float dt);
    void ProcessMouseInput(float xoffset, float yoffset);
    void Update(float deltaTime);
    void Render();
    void spawn_block(std::string shader_name, std::string texture_name, bool shooting_block = false);

    bool check_collisions(GameObject &obj);
    bool check_collision(GameObject &one, GameObject &two);
};
#endif
