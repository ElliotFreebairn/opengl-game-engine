#ifndef LEVEL_H
#define LEVEL_H

#include "block.h"
#include "resource_manager.h"
#include "shader.h"

#include <iostream>
#include <list>

class Level {
public:
    Level();
    Level(std::string filename);

    void save_map(std::string file_to_save);
    void load_map(std::string file_to_load);

    void add_block(Block &block);
    void add_blocks(std::list<Block> &blocks);
    void draw();

    std::list<Block>& get_blocks();

private:
    std::list<Block> blocks;
};

#endif
