#ifndef _LEVEL_HPP_
#define _LEVEL_HPP_

#include "Block.hpp"
#include <vector>

class Level {
public:
    int width;
    int height;

    std::vector<Block> tile;

    Level(int width_, int height_, int seed);
    Level();
    ~Level();

    Block getBlock(int x, int y);
};

#endif // _LEVEL_HPP_
