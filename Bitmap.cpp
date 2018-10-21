#include "Bitmap.hpp"
#include <iostream>

Bitmap::Bitmap(int width_, int height_, sf::Uint32 &pixels_)
 :  width(width_),
    height(height_) {
    pixels = &pixels_;
}

Bitmap::Bitmap(int width_, int height_)
 :  width(width_),
    height(height_) {
    notBG = true;
    sf::Uint32 other[width * height];
    pixels = other;
}

Bitmap::Bitmap() {
}

Bitmap::~Bitmap() {

}

void Bitmap::render(const Bitmap &b, int ox, int oy) {
    //std::cout << "!!!!!!!!!!!" << std::endl;
    for (int y = 0; y < b.height; ++y) {
        int yy = y + oy;

        if (yy < 0 || yy >= height) {
            continue;
        }

        for (int x = 0; x < b.width; ++x) {
            int xx = x + ox;
            if (xx < 0 || xx >= width) {
                continue;
            }

            sf::Uint32 alpha = b.pixels[x + y * b.width];

            if (alpha > 0) {
                pixels[xx + yy * width] = b.pixels[x + y * b.width];
            }
            //pixels[xx + yy * width] = alpha;
        }
    }
}

void Bitmap::clear() {
    size_t pixSize = width * height;
    for (unsigned int i = 0; i < pixSize; ++i) {
        pixels[i] = 0;
    }
}

