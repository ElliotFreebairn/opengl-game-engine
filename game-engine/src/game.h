#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Game
{
public:
    Game();
    Game(unsigned int width, unsigned int height);
    ~Game();

    bool keys[1024];
    unsigned int width, height;

    // init game state (load all shaders/textures/levels)
    void Init();
    // game loop
    void ProcessInput(float dt);
    void ProcessMouseInput(float xoffset, float yoffset);
    void Update(float deltaTime);
    void Render();
};
#endif