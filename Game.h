#pragma once
#include "Ball.h"
#include "Brick.h"
#include "Deck.h"
#include <list>

class Game
{
public:
    Ball _myBall;
    std::list <Brick> _bricks;
    Deck _myDeck;
public:
    void initScene();
    bool isCollision(Ball const &currentBall, Brick const &currentBrick) const;
    void changeTrajectory(Ball &currentBall, Brick const &currentBrick, bool const isDeck) const;
    Game(void);
    ~Game(void);
};
