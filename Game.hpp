#ifndef _GAME_HPP_
#define _GAME_HPP_

#include "Player.hpp"
#include "Level.hpp"

class Game {
public:
    int random;

    Level level;
    Player player;
    int time;

    Game();
    ~Game();

    void update();

};

#endif // _GAME_HPP_



