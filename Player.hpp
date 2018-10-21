#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

class Player {
public:
    double x, y, xd, yd, rd, rot;
    Player();
    ~Player();

    void update();
};

#endif // _PLAYER_HPP_
