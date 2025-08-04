#ifndef GAME_H
#define GAME_H

#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "game_level.h"
#include "game_object.h"

enum GameState {
  GAME_ACTIVE,
  GAME_MENU,
  GAME_WIN 
};

class Game 
{
public:
  // game state
  GameState State;
  bool Keys[1024];
  unsigned int Width, Height;
  // game levels
  std::vector<GameLevel> Levels;
  unsigned int Level;
  // constructor/destructor
  Game(unsigned int width, unsigned int height);
  ~Game();
  // intilalise game state (loads all shaders/textures/levels)
  void Init();
  // game loop
  void ProcessInput(float dt);
  void Update(float dt);
  void Render();

  void DoCollisions();
};

#endif
