#include "game.h"
#include "resource_manager.h"
#include "sprite_renderer.h"
#include "game_object.h"

// Game-related state data
SpriteRenderer *Renderer;

Game::Game(unsigned int width, unsigned int height) 
  : State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{

}

Game::~Game()
{
  delete Renderer;
}

void Game::Init()
{
  // load shaders
  ResourceManager::LoadShader("shaders/sprite.vs", "shaders/sprite.fs", nullptr, "sprite");
  // configure shaders
  glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width),
                                    static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
  ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
  ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
  // set render specific controls
  Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
  // load textures
  ResourceManager::LoadTexture("textures/background.jpg", false, "background");
  ResourceManager::LoadTexture("textures/awesomeface.png", true, "face");
  ResourceManager::LoadTexture("textures/block.png", false, "block");
  ResourceManager::LoadTexture("textures/block_solid.png", false, "block_solid");
  // load levels
  GameLevel one; one.Load("src/levels/one.lvl", Width, Height / 2);
  GameLevel two; two.Load("src/levels/two.lvl", Width, Height / 2);
  GameLevel three; three.Load("src/levels/three.lvl", Width, Height / 2);
  GameLevel four; four.Load("src/levels/four.lvl", Width, Height / 2);
  this->Levels.push_back(one);
  this->Levels.push_back(two);
  this->Levels.push_back(three);
  this->Levels.push_back(four);
  this->Level = 0;
  
}
void Game::Update(float dt)
{

}

void Game::ProcessInput(float dt) {

}

void Game::Render()
{
  Renderer->DrawSprite(ResourceManager::GetTexture("background"),
                       glm::vec2(200.0f, 200.0f), glm::vec2(300.0f, 400.0f),
                       45.0f, glm::vec3(0.0f, 1.0, 0.0f));
  // draw level
  this->Levels[Level].Draw(*Renderer);
}
