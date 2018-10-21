#include "Screen.hpp"
#include <random>
#include <cmath>

Screen::Screen() {
}

Screen::Screen(int width_, int height_, sf::Uint32 &pixels_)
 :  Bitmap(width_, height_, pixels_) {
    perspectiveVision = Bitmap3D(width, height, pixels_);
}

Screen::~Screen() {
}

int t;

void Screen::render(Game &game) {

    //clear();
    perspectiveVision.render(game);
    perspectiveVision.renderFog();

}

void Screen::update() {

}


