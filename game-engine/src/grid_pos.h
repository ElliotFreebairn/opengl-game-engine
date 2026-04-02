#ifndef GRID_POS_H
#define GRID_POS_H

struct GridPos {
  int x;
  int y;
  int z;

  GridPos() : x(0), y(0), z(0) {}
  GridPos(int x, int y, int z) : x(x), y(y), z(z) {}

  bool operator==(const GridPos& other) const {
    return x == other.x && y == other.y && z == other.z;
  }
};
#endif