#ifndef LEVEL_H
#define LEVEL_H

#include "block_cell.h"
#include "resource_manager.h"
#include "shader.h"

#include <iostream>
#include <list>

const int WORLD_X = 64;
const int WORLD_Y = 32;
const int WORLD_Z = 64;

const int WORLD_OFFSET_X = WORLD_X / 2;
const int WORLD_OFFSET_Y = WORLD_Y / 2;
const int WORLD_OFFSET_Z = WORLD_Z / 2;

class Level {
private:
    BlockCell blocks[WORLD_X][WORLD_Y][WORLD_Z];

public:
    Level();
    Level(std::string filename);

    void save_map(std::string file_to_save);
    void load_map(std::string file_to_load);
    
    BlockCell get_block(int x, int y, int z) const;
    void set_block(int x, int y, int z, BlockCell cell);
    bool is_air(int x, int y, int z) const;
    bool in_bounds(int x, int y, int z) const;
    void draw();

    void damage_block(int x, int y, int z);

//    void add_block(Block &block);
//    void add_blocks(std::list<Block> &blocks);
//    void draw();
//
//    std::list<Block>& get_blocks();

};

#endif
