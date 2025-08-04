#include "game.h"
#include "resource_manager.h"
#include "sprite_renderer.h"
#include "game_object.h"
#include "ball_object.h"

// Game-related state data
SpriteRenderer *Renderer;

const glm::vec2 PLAYER_SIZE(100.f, 20.0f);
const float PLAYER_VELOCITY(500.0f);

const glm::vec2 INITIAL_BALL_VELOCITY(100.0f, -350.f);
const float BALL_RADIUS = 12.5f;

GameObject *Player;
BallObject *Ball;

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
  ResourceManager::LoadTexture("textures/paddle.png", true, "paddle");
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

  glm::vec2 playerPos = glm::vec2(Width / 2.0f - PLAYER_SIZE.x / 2.0f,
                                  Height - PLAYER_SIZE.y);
  Player = new GameObject(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("paddle"));

  glm::vec2 ballPos = playerPos + glm::vec2(PLAYER_SIZE.x / 2.0f - BALL_RADIUS, -BALL_RADIUS * 2.0f);
  Ball = new BallObject(ballPos, BALL_RADIUS, INITIAL_BALL_VELOCITY, ResourceManager::GetTexture("face"));
  
}
void Game::Update(float dt)
{
  Ball->Move(dt, Width);

  DoCollisions();
}

void Game::ProcessInput(float dt) {
  if (State == GAME_ACTIVE)
  {
    float velocity = PLAYER_VELOCITY * dt;
    // move playerboard
    if (Keys[GLFW_KEY_A])
    {
      if (Player->Position.x >= 0.0f)
        Player->Position.x -= velocity;
        if(Ball->Stuck)
          Ball->Position.x -= velocity;
    }
    if (Keys[GLFW_KEY_D])
    {
    if (Player->Position.x <= Width - Player->Size.x)
      Player->Position.x += velocity;
      if (Ball->Stuck)
        Ball->Position.x += velocity;
    }
    if (Keys[GLFW_KEY_SPACE])
      Ball->Stuck = false;
  }
}

void Game::Render()
{
  Renderer->DrawSprite(ResourceManager::GetTexture("background"),
                       glm::vec2(200.0f, 200.0f), glm::vec2(300.0f, 400.0f),
                       45.0f, glm::vec3(0.0f, 1.0, 0.0f));
  // draw level
  this->Levels[Level].Draw(*Renderer);
  Player->Draw(*Renderer);
  Ball->Draw(*Renderer);
}

bool CheckCollision(GameObject &one, GameObject &two);

void Game::DoCollisions()
{
  for (GameObject &box :  Levels[Level].Bricks)
  {
    if (!box.Destroyed)
    {
      if (CheckCollision(*Ball, box))
        box.Destroyed = true;
    }
  }
}



bool CheckCollision(GameObject &one, GameObject &two) // AABB - AABB
{
  // collision x-axis?
  bool collisionX = one.Position.x + one.Size.x >= two.Position.x &&
                    two.Position.x + two.Size.x >= one.Position.x;
  // collision y-axis?
  bool collisionY = one.Position.y + one.Size.y >= two.Position.y &&
                    two.Position.y + two.Size.y >= one.Position.y;

  return collisionX && collisionY;
}

