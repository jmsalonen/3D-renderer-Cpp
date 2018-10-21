#include <SFML/Graphics.hpp>

#include "Player.hpp"
#include <cmath>
#include <iostream>

Player::Player()
 :  x(0),
    y(0),
    xd(0),
    yd(0),
    rd(0),
    rot(0) {
}

Player::~Player() {
}

void Player::update() {
    double wSpeed = 0.008;
    double rSpeed = 0.008;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        ++xd;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        --xd;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        --yd;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        ++yd;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        ++rd;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        --rd;

    double rCos = std::cos(rot);
    double rSin = std::sin(rot);

    x += (xd * -rSin + yd * rCos) * wSpeed;
    y += (xd * rCos + yd * rSin) * wSpeed;

    rot += rd * rSpeed;
    xd *= 0.9;
    yd *= 0.9;
    rd *= 0.9;
}



