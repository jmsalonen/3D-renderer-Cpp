#ifndef _SCREEN_HPP_
#define _SCREEN_HPP_

#include "Bitmap.hpp"
#include "Bitmap3D.hpp"
#include "Game.hpp"

class Screen : public Bitmap {

public:
    Bitmap test;
    Bitmap3D perspectiveVision;

    Screen();
    Screen(int width_, int height_, sf::Uint32 &pixels_);
    ~Screen();

    void render(Game &game);
    void update();

};

#endif // _SCREEN_HPP_

