#pragma once
#include "Structs.h"
#include "Brick.h"

class Deck: public Brick
{
private:
    Speed _speed;
private:
    Speed reductionSpeed();
public:
    friend class Game;
    Deck();
    Deck(float const &width, float const &height, float const &length, float const &x, float const &y,float const &z);
    ~Deck(void);
    Speed increaseSpeed(float const &deltaSpeedX, float const &deltaSpeedY, float const &deltaSpeedZ);

    void move(float const &dt);
};
