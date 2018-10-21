#ifndef _BITMAP_HPP_
#define _BITMAP_HPP_

#include <SFML/Graphics.hpp>
#include <vector>

class Bitmap {
    bool isSprite = false;
public:
    int width;
    int height;
    bool notBG = false;
    sf::Uint32* pixels;

    Bitmap(int width_, int height_, sf::Uint32 &pixels_);
    Bitmap(int width_, int height_);
    Bitmap();
    ~Bitmap();

    void render(const Bitmap &b, int ox, int oy);
    void clear();
};

#endif // _BITMAP_HPP_

