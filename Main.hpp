#ifndef _MAIN_HPP_
#define _MAIN_HPP_

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "Screen.hpp"
#include "Game.hpp"

class Main {
public:
    //const int WIDTH = 1366 / 2;
    //const int HEIGHT = 768 / 2;
    const int WIDTH = 640 / 1;
    const int HEIGHT = WIDTH * 3 / 4;
    const int SCALE = 1;
    const int FRAME_LIMIT = 60;
    const std::string TITLE = "3D Renderer";

    sf::Clock clock;
    sf::Event event;
    sf::Image image;
    sf::Sprite sprite;
    sf::Uint8* pixels;
    sf::Uint32* rgba;

private:
    sf::RenderWindow window;
    bool isRunning = true;
    Screen screen;
    Game game;

    void createWindow();
public:

    Main();
    ~Main();
    void run();
    void render();
    void update();
    void stop();
    void quit();

};

#endif // _MAIN_HPP_

