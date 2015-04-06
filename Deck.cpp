#include <stdio.h>
#include "Deck.h"

Deck::Deck()
{
    _size.width = 0.5f;
    _size.height = 0.5f;
    _size.length = 0.1f;

    _pos.x = 0.f;
    _pos.y = -2.f;
    _pos.z = -5.f;

    _speed.X = 0.f;
    _speed.Y = 0.f;
    _speed.Z = 0.f;
}

Deck::Deck(float const &width, float const &height, float const &length, float const &x, float const &y, float const &z)
{
    _size.height = height;
    _size.width = width;
    _size.length = length;

    _pos.x = x;
    _pos.y = y;
    _pos.z = z;

    _speed.X = 0.f;
    _speed.Y = 0.f;
    _speed.Z = 0.f;
}

Speed Deck::increaseSpeed(float const &deltaSpeedX, float const &deltaSpeedY, float const &deltaSpeedZ)
{ 
    const float k = 0.07f;
    _speed.X += deltaSpeedX * k;
    _speed.Y += deltaSpeedY * k;
    _speed.Z += deltaSpeedZ * k;
    return _speed;
}

Speed Deck::reductionSpeed()
{
    const float reductionFactor = 1.1f;
    _speed.X /= (reductionFactor );
    _speed.Y /= (reductionFactor );
    _speed.Z /= (reductionFactor );
    return _speed;
}

void Deck::move(float const &dt)
{
    _pos.x += _speed.X * dt;
    _pos.y += _speed.Y * dt;
    _pos.z += _speed.Z * dt;
    recallGeometry();
    reductionSpeed();
}

Deck::~Deck(void)
{}
