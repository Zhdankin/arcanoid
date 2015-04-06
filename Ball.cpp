#include <math.h>
#include <glut.h>
#include "Ball.h"

void Ball::draw() const
{
    glColor3f(0.0f, 0.0f, 1.0f);
    glPushMatrix();
    glTranslatef(_pos.x, _pos.y, _pos.z);
    {
        glutSolidSphere(_size, 20, 20);
    }
    glPopMatrix();
}

void Ball::move(float const &dt)
{
    _pos.x += _speed.X * dt;
    _pos.y += _speed.Y * dt;
    _pos.z += _speed.Z * dt;

    //wall collision 
    //2 is size of scene
    if (_pos.x > 2.f) {_speed.X = -fabs(_speed.X);}
    if (_pos.x < -2.f) {_speed.X = fabs(_speed.X);}

    if (_pos.y > 2.f)    {_speed.Y = -fabs(_speed.Y);}
    if (_pos.y < -2.5f) {_speed.Y = fabs(_speed.Y);}

    if (_pos.z > 2.f) {_speed.Z = -fabs(_speed.Z);}
    if (_pos.z < -2.f) {_speed.Z = fabs(_speed.Z);}
}

void Ball::setPossition(DimensionPossition const &newPosition)
{
    _pos = newPosition;
}

void Ball::setPossition(float const &X, float const &Y, float const &Z)
{
    _pos.x = X;
    _pos.y = Y;
    _pos.z = Z;
}

void Ball::setSpeed(float const &speedX, float const &speedY, float const &speedZ)
{
    _speed.X = speedX;
    _speed.Y = speedY;
    _speed.Z = speedZ;
}

Ball::Ball(): _size(0.05), _isRunning(false)
{
    _pos.x = 0.f;
    _pos.y = 0.f;
    _pos.z = -5.f;

    _speed.X = 0.f;
    _speed.Y = 0.f;
    _speed.Z = 0.f;
}

bool Ball::isRunning() const
{
    return _isRunning;
}

void Ball::setRunning(bool const &running)
{
    _isRunning = running;
}

Ball::Ball(float const &ballSize, DimensionPossition const &startPossition, Speed const &startSpeed): _isRunning(false)
{
    _size = ballSize; //radius
    _pos = startPossition;
    _speed = startSpeed;
}

Ball::~Ball()
{


}
