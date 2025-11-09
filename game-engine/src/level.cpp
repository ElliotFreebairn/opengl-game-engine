#include "level.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

Level::Level()
{

}

Level::Level(std::string filename)
{

}

void Level::draw()
{
    for (Block &block : blocks)
    {
        block.draw();
    }
}

void Level::add_block(Block &block)
{
    blocks.push_back(block);
}

void Level::add_blocks(std::list<Block> &blocks)
{
    this->blocks.insert(this->blocks.end(), blocks.begin(), blocks.end());
}

void Level::save_map(std::string file_to_save)
{
    /*
        File format:
        
        Each line is a block: position, colour?
        shader id, texture id, x, y, z
    */
    std::ofstream file(file_to_save + ".txt");
    
    for (Block &block : blocks)
    {
        std::string block_line = 
            block.get_shader_name() + "," +
            block.get_texture_name() + "," +
            block.position_to_str(); 

        file << block_line;
        file << "\n";
    }

    file.close();
}

void Level::load_map(std::string file_to_load)
{
    std::string myText;
    std::ifstream file(file_to_load + ".txt");

    while (getline(file, myText)) {
        std::vector<std::string> render_info;
        std::vector<float> pos_info;
        std::stringstream ss(myText);
        std::string split;
        
        std::cout << "myText " << myText << std::endl;
        char del = ',';

        int count = 0;
        while (getline(ss, split, del)) {
            if (count < 2) {
                render_info.push_back(split);
            } else {
                pos_info.push_back(std::stoi(split));
            }
            count++;
        }
        
        
        std::string shader_name = render_info[0];
        std::string texture_name = render_info[1];
        glm::vec3 pos(pos_info[0], pos_info[1], pos_info[2]);

        Block new_block(shader_name, texture_name, pos);
        add_block(new_block);
    }
}
