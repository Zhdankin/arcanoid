#pragma once
#include "Structs.h"


class Ball
{
private:
    double _size; //radius
    DimensionPossition _pos;
    Speed _speed;
    bool _isRunning;

public:
    friend class Game;
    Ball();
    Ball(float const &ballSize, DimensionPossition const &startPossition, Speed const &startSpeed);
    ~Ball();
    void draw() const;
    void move(float const &dt);
    void setPossition(DimensionPossition const &newPosition);
    void setPossition(float const &X, float const &Y, float const &Z);
    void setSpeed(float const &speedX, float const &speedY, float const &speedZ);
    bool isRunning() const;
    void setRunning(bool const &running);
};
