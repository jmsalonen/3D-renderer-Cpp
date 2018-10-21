#include "Main.hpp"
#include <iostream>
#include <cstdint>

Main::Main() {
    pixels = new sf::Uint8[WIDTH * HEIGHT * 4]; // NEW
    rgba = new sf::Uint32[WIDTH * HEIGHT]; // NEW

    game = Game();
    screen = Screen(WIDTH, HEIGHT, *rgba);
}
Main::~Main() {
    delete[] pixels; // DELETE
    delete[] rgba; // DELETE
}

void Main::createWindow() {
    if (window.isOpen())  {
        window.close();
    }

    window.create(sf::VideoMode(WIDTH, HEIGHT), TITLE, sf::Style::Close); //sf::Style::None
    sf::Vector2u windowSize;
    windowSize.x = WIDTH * SCALE;
    windowSize.y = HEIGHT * SCALE;
    window.setKeyRepeatEnabled(true);
    window.setFramerateLimit(FRAME_LIMIT);
    sf::Vector2i position = window.getPosition();
    // resolution scale
    sf::Vector2u res = window.getSize();
    res.x *= SCALE;
    res.y *= SCALE;
    window.setSize(res);
    // set window position
    position.x = 100;
    position.y = 50;
    window.setPosition(position);
}

void Main::run() {
    createWindow();

    while(isRunning) {
        /* EVENTS */
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                stop();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                stop();
            }
        }

        /////////
        //float framerate = 1.f / clock.getElapsedTime().asSeconds();
        //clock.restart();

        update();

        /* DRAW */
        //window.clear();
        render();

    }

    stop();
}

void Main::render() {

    screen.render(game);

    for (int i = 0; i < WIDTH * HEIGHT; ++i) {
        pixels[i * 4 + 0] = rgba[i] >> 16;
        pixels[i * 4 + 1] = rgba[i] >> 8;
        pixels[i * 4 + 2] = rgba[i];
        pixels[i * 4 + 3] = 255;
    }

    //void* temp = reinterpret_cast<void*>(rgba);
    //pixels = reinterpret_cast<sf::Uint8*>(rgba);
    // draw image SFML style
    image.create(WIDTH, HEIGHT, pixels);
    sf::Texture texture;
    texture.loadFromImage(image);
    sprite.setTexture(texture, true);
    window.draw(sprite);
    window.display();
}

void Main::update() {
    game.update();
    screen.update();
}

void Main::stop() {
    if (!isRunning) {
        return;
    }

    window.close();
    isRunning = false;
}

/* MAIN */

int main() {

    Main mainGame;
    //sf::Mouse::setPosition(sf::Vector2i((game.WIDTH-1)/2, (game.HEIGHT-1)/2));
    mainGame.run();
    return EXIT_SUCCESS;
}


