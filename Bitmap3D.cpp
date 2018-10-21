#include "Bitmap3D.hpp"
#include <cmath>

#include <iostream>
#include <vector>

Bitmap3D::Bitmap3D(int width_, int height_, sf::Uint32 &pixels_)
 :  Bitmap(width_, height_, pixels_) {
    depthBuffer = std::vector<double>(width_ * height_);
    depthBufferWall = std::vector<double>(width_);
}
Bitmap3D::Bitmap3D()
 :  Bitmap() {
}

Bitmap3D::~Bitmap3D() {
}

void Bitmap3D::render(Game &game) {

    for (int x = 0; x < width; ++x) {
      depthBufferWall[x] = 0;
    }

    fov = height;

    //xCam = 0; //game.time % 100.0 / 50;
    //yCam = 0; //game.time % 100.0 / 50;
    //zCam = 0; //std::sin(game.time / 10.0) * 2;
    //rot = std::sin(game.time / 40.0) * 0.5;
    xCam = game.player.x;
    yCam = game.player.y;
    rot = game.player.rot;

    rSin = std::sin(rot);
    rCos = std::cos(rot);

    Level level = game.level;

    for (int y = 0; y < height; ++y) {
        double yd = ((y + 0.5) - (height / 2)) / fov;
        //double yd = ((y + updown) - (height / 2)) / fov;
        double zd = (4 + zCam) / yd;

        if (yd < 0) {
            zd = (4 - zCam) / -yd;
        }

        for (int x = 0; x < width; ++x) {

            double xd = (x - (width / 2)) / fov;
            xd *= zd;

            double xx = xd * rCos - zd * rSin + (xCam + 0.5) * 8;
            double yy = xd * rSin + zd * rCos + (yCam) *  8;

            int xPix = (int) xx * 2;
            int yPix = (int) yy * 2;

            if (xx < 0)
              xPix--;
            if (yy < 0)
              yPix--;

            depthBuffer[x + y * width] = zd;
            //pixels[x + y * width] = ((yPix & 15) * 16) << 8 | ((xPix & 15) * 16);
            pixels[x + y * width] = 0x00808080;
/*
            drawFloor(xx, yy, yd, x, y, xPix, yPix, 0, 2);
            drawFloor(xx, yy, yd, x, y, xPix, yPix, 0, 3);
            drawFloor(xx, yy, yd, x, y, xPix, yPix, 1, 2);
            drawFloor(xx, yy, yd, x, y, xPix, yPix, 1, 3);
*/
        }

    }
    /*
    renderWall(0, 2, 1, 2);
    renderWall(0, 1, 0, 2);
    renderWall(-0.2, 1, -0.2, 2);
    renderWall(1, 2, 1, 1);
    renderWall(1, 1, 1, 0);
    renderWall(0, 2, 1, 2);
    renderWall(1, 2, 2, 2);
    renderWall(2, 2, 2, 1);
    */


    // level
    for (int y = -1; y <= level.height; ++y) {
        for (int x = -1; x <= level.width; ++x) {
            Block c = level.getBlock(x, y);
            Block e = level.getBlock(x + 1, y);
            Block w = level.getBlock(x - 1, y);
            Block s = level.getBlock(x, y - 1);
            Block n = level.getBlock(x, y + 1);

            if (!c.SOLID)
                continue;

            if (!e.SOLID) {
                renderWall(x + 1, y, x + 1, y + 1);
            }
            if (!w.SOLID) {
                renderWall(x, y + 1, x, y);
            }
            if (!s.SOLID) {
                renderWall(x, y, x + 1, y);
            }
            if (!n.SOLID) {
                renderWall(x + 1, y + 1, x, y + 1);
            }
        }
    }

}


void Bitmap3D::renderWall(double x0, double y0, double x1, double y1) {

    double xo0 = x0 - 0.5 - xCam;
    double u0 = - 0.5 + zCam / 8;
    double d0 = + 0.5 + zCam / 8;
    double zo0 = y0 - yCam;

    double xx0 = xo0 * rCos + zo0 * rSin;
    double zz0 = -xo0 * rSin + zo0 * rCos;

    double xo1 = x1 - 0.5 - xCam;
    double u1 = - 0.5 + zCam / 8;
    double d1 = + 0.5 + zCam / 8;
    double zo1 = y1 - yCam;

    double xx1 = xo1 * rCos + zo1 * rSin;
    double zz1 = -xo1 * rSin + zo1 * rCos;

    double t0 = 0;
    double t1 = 16;

    double clip = 0.1;

    if (zz0 < clip) {
        double p = (clip - zz0) / (zz1 - zz0);
        zz0 = zz0 + (zz1 - zz0) * p;
        xx0 = xx0 + (xx1 - xx0) * p;
        t0 = t0 + (t1 - t0) * p;
    }

    if (zz1 < clip) {
        double p = (clip - zz1) / (zz1 - zz0);
        zz1 = zz1 + (zz1 - zz0) * p;
        xx1 = xx1 + (xx1 - xx0) * p;
        t1 = t1 + (t1 - t0) * p;
    }

    double xPixel0 = xx0 / zz0 * fov + width / 2.0;
    double xPixel1 = xx1 / zz1 * fov + width / 2.0;

    if (xPixel0 > xPixel1)
        return;
    int xp0 = (int) std::ceil(xPixel0);
    int xp1 = (int) std::ceil(xPixel1);
    if (xp0 < 0)
        xp0 = 0;
    if (xp1 > width)
        xp1 = width;

    double yPixel00 = (u0 / zz0 * fov + height / 2.0) + 0.5;
    double yPixel10 = (u1 / zz1 * fov + height / 2.0) + 0.5;
    double yPixel01 = (d0 / zz0 * fov + height / 2.0) + 0.5;
    double yPixel11 = (d1 / zz1 * fov + height / 2.0) + 0.5;

    double iz0 = 1 / zz0;
    double iz1 = 1 / zz1;

    double xt0 = t0 * iz0;
    double xt1 = t1 * iz1;

    for (int x = xp0; x < xp1; ++x) {

        double p = (x - xPixel0) / (xPixel1 - xPixel0);
        double yPixel0 = yPixel00 + (yPixel10 - yPixel00) * p;
        double yPixel1 = yPixel01 + (yPixel11 - yPixel01) * p;
        double iz = iz0 + (iz1 - iz0) * p;

        if (depthBufferWall[x] > iz) {
            continue;
        }
        depthBufferWall[x] = iz;


        int xTex = (int) ((xt0 + (xt1 - xt0) * p) / iz);

        if (xPixel0 > xPixel1)
            return;
        int yp0 = (int) yPixel0;
        int yp1 = (int) yPixel1;
        if (yp0 < 0)
            yp0 = 0;
        if (yp1 > height)
            yp1 = height;

        for (int y = yp0; y < yp1; ++y) {

        double py = (y - yPixel0) / (yPixel1 - yPixel0);
            int yTex = (int)(py * 16);

            depthBuffer[x + y * width] = 12 / iz;
            //pixels[x + y * width] = xTex * 64 | yTex * 64 << 8;
            pixels[x + y * width] = 0x00C0C0C0;
        }

    }

}


void Bitmap3D::drawFloor(double xd, double zd, double yd, int x, int y, int xPix, int yPix, int pX, int pY) {
    if (yd <= 0) return;

    if (xd >= pX * 16 && xd < pX * 16 + 16 && zd >= pY * 16 && zd < pY * 16 + 16) {
        pixels[x + y * width] = 0xff00ff00;
    }
}

void Bitmap3D::drawCeiling(double xd, double zd, double yd, int x, int y, int xPix, int yPix, int pX, int pY) {
    if (yd >= 0) return;

    if (xd >= pX * 16 && xd < pX * 16 + 16 && zd >= pY * 16 && zd < pY * 16 + 16) {
        pixels[x + y * width] = 0xff00ff00;
    }
}

void Bitmap3D::renderFog() {

    for (int i = 0; i < depthBuffer.size(); ++i) {
        int color = pixels[i];
        int r = (color >> 16) & 0xff;
        int g = (color >> 8) & 0xff;
        int b = (color) & 0xff;

        double brightness = 50000 / (depthBuffer[i] * depthBuffer[i]);

        if (brightness < 0)
            brightness = 0;
        if (brightness > 255)
            brightness = 255;

        if ((int) (r / 255.0 * brightness) < 1)
            r = 0;
        else
            r = (int) (r / 255.0 * brightness);
        if ((int) (g / 255.0 * brightness) < 1)
            g = 0;
        else
            g = (int) (g / 255.0 * brightness);
        if ((int) (b / 255.0 * brightness) < 1)
            b = 0;
        else
            b = (int) (b / 255.0 * brightness);
        //pixels[i] = r << 16 | g << 8 | b;
        pixels[i] = r << 16 | g << 8 | b;
    }

}

