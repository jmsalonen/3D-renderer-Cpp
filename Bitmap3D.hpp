#ifndef _BITMAP3D_HPP_
#define _BITMAP3D_HPP_

#include "Bitmap.hpp"
#include "Game.hpp"

class Bitmap3D : public Bitmap {
    double xCam, yCam, zCam, rot, rSin, rCos, fov;
    std::vector<double> depthBuffer;
    std::vector<double> depthBufferWall;
public:
    Bitmap3D(int width_, int height_, sf::Uint32 &pixels_);
    Bitmap3D();
    ~Bitmap3D();

    void render(Game &game);
    void renderFog();
    void drawFloor(double xd, double zd, double yd, int x, int y, int xPix, int yPix, int pX, int pY);
    void drawCeiling(double xd, double zd, double yd, int x, int y, int xPix, int yPix, int pX, int pY);
    void renderWall(double x0, double y0, double x1, double y1);


};

#endif // _BITMAP3D_HPP_

