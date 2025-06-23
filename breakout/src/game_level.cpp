#include "game_level.h"

void GameLevel::Load(const char *file, unsigned int levelWidth, unsigned int levelHeight)
{
  // clear old data
  Bricks.clear();
  // load from file
  unsigned int tileCode;
  GameLevel level;
  std::string line;
  std::ifstream fstream(file);
  std::vector<std::vector<unsigned int>> tileData;
  if (fstream)
  {
    while (std::getline(fstream, line)) // read each line from file
    {
      std::istringstream sstream(line);
      std::vector<unsigned int> row;
      while (sstream >> tileCode) // read each word
      {
        row.push_back(tileCode);
      }
      tileData.push_back(row);
    }
    if (tileData.size() > 0)
    {
      init(tileData, levelWidth, levelHeight);
    }
  }
}


