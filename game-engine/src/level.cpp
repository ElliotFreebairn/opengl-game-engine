#include "level.h"
#include "block.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include <vector>

inline int to_index_x(int x) { return x + WORLD_OFFSET_X; }
inline int to_index_y(int y) { return y + WORLD_OFFSET_Y; }
inline int to_index_z(int z) { return z + WORLD_OFFSET_Z; }

std::string block_type_to_texture(BlockType type)
{
    switch (type) {
        case BlockType::Dirt:
            return "dirt_block";
        case BlockType::Cobblestone:
            return "cobblestone_block";
        case BlockType::Oak:
            return "oak_block";
        default:
            return "";
    }
}

Level::Level()
{
    for (int x = 0; x < WORLD_X; x++) {
        for (int y = 0; y < WORLD_Y; y++) {
            for (int z = 0; z < WORLD_Z; z++) {
                blocks[x][y][z].type = BlockType::Air;
                blocks[x][y][z].health = 10;
            }
        }
    }
}

Level::Level(std::string filename)
{
    load_map(filename);
}

bool Level::in_bounds(int x, int y, int z) const    
{
    int ix = x + WORLD_OFFSET_X;
    int iy = y + WORLD_OFFSET_Y;
    int iz = z + WORLD_OFFSET_Z;

    return ix >= 0 && ix < WORLD_X &&
        iy >= 0 && iy < WORLD_Y &&
        iz >= 0 && iz < WORLD_Z;
}

BlockCell Level::get_block(int x, int y, int z) const
{
    if (!in_bounds(x, y, z)) {

        return BlockCell{};
    }
    
    int ix = x + WORLD_OFFSET_X;
    int iy = y + WORLD_OFFSET_Y;
    int iz = z + WORLD_OFFSET_Z;

    return blocks[ix][iy][iz];
}

void Level::set_block(int x, int y, int z, BlockCell cell)
{
    if (!in_bounds(x, y, z)) {
        return;
    }

    int ix = x + WORLD_OFFSET_X;
    int iy = y + WORLD_OFFSET_Y;
    int iz = z + WORLD_OFFSET_Z;

    blocks[ix][iy][iz].type = cell.type;
    blocks[ix][iy][iz].health = cell.health;
}

bool Level::is_air(int x, int y, int z) const
{
    if (!in_bounds(x ,y ,z)) {
        return true;
    }

    int ix = x + WORLD_OFFSET_X;
    int iy = y + WORLD_OFFSET_Y;
    int iz = z + WORLD_OFFSET_Z;

    return blocks[ix][iy][iz].type == BlockType::Air;
}

void Level::draw()
{
    for (int ix = 0; ix < WORLD_X; ix++) {
        for (int iy = 0; iy < WORLD_Y; iy++) {
            for (int iz = 0; iz < WORLD_Z; iz++) {
                BlockCell cell = blocks[ix][iy][iz];

                if (cell.type == BlockType::Air)
                    continue;

                int x = ix - WORLD_OFFSET_X;
                int y = iy - WORLD_OFFSET_Y;
                int z = iz - WORLD_OFFSET_Z;
                
                std::string texture_name = block_type_to_texture(cell.type);

                Block block("rectangle", texture_name, glm::vec3(x, y, z));
                block.draw();
            }
        }
    }
}

void Level::damage_block(int x, int y, int z)
{
    BlockCell cell = get_block(x, y, z); 

    if (is_air(x, y, z)) {
        return;
    }
    
    cell.health -= 1;
    if (cell.health == 0) {
        cell.type = BlockType::Air;
    }

    set_block(x, y, z, cell);
}

void Level::save_map(std::string file_to_save)
{
    /*
        File format:
        
        Each line is a block: position, colour?
        shader id, texture id, x, y, z
    */
    std::ofstream file(file_to_save + ".txt");
    
    for (int x = 0; x < WORLD_X; x++) {
        for (int y = 0; y < WORLD_Y; y++) {
            for (int z = 0; z < WORLD_Z; z++) {
                BlockCell cell = blocks[x][y][z];

                if (cell.type == BlockType::Air)
                    continue;

                file << x << "," << y << "," << z << "," << static_cast<int>(cell.type) << "\n";
            }
        }
    }
    file.close();
}

void Level::load_map(std::string file_to_load)
{
    for (int x = 0; x < WORLD_X; x++) {
        for (int y = 0; y < WORLD_Y; y++) {
            for (int z = 0; z < WORLD_Z; z++) {
                blocks[x][y][z].type = BlockType::Air;
            }
        }
    }

    std::ifstream file(file_to_load + ".txt");
    std::string line;

    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string split;

        std::vector<int> values;

        while (getline(ss, split, ',')) {
            values.push_back(std::stoi(split));
        }

        if (values.size() != 4) {
            continue;
        }

        int x = values[0];
        int y = values[1];
        int z = values[2];
        //BlockType type = static_cast<BlockType>(values[3]);

        //set_block(x, y, z, type);
    }
}
