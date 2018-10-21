#include "Level.hpp"
#include <cstdlib>

Level::Level() {
}

Level::Level(int width_, int height_, int seed)
 :  width(width_),
    height(height_) {
    tile = std::vector<Block>(width * height);
    std::srand(seed);
    for (int i = 0; i < tile.size(); ++i) {
        int random = std::rand() % 10;
        if (random < 3)
            tile[i] = Block(true);
        else
            tile[i] = Block(false);
    }

}

Block Level::getBlock(int x, int y) {
    if (x < 0 || y < 0 || x >= width || y >= height) {
        return Block(true);
    }
    return tile[x + y * width];
}

Level::~Level() {
}


