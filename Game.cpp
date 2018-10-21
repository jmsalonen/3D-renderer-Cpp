#include <cstdlib>
#include "Game.hpp"
#include "Level.hpp"

Game::Game() {
    player = Player();
    random = rand();
    level = Level(32, 32, random);
}

Game::~Game() {
}

void Game::update() {
    ++time;
    player.update();
}


