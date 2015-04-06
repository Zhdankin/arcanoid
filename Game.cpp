#include "Game.h"


void Game::initScene()
{
    // init _bricks
    int brickCountInOneRow;
    int RowsCount;

    const float leftCoordinate = -2.f;
    const float horisontalStep = 1.f;

    const float downCoordinate = -1.f;
    const float verticalStep = 0.5f;
    
    RowsCount = 0;
    do
    {
        brickCountInOneRow = 0;
        do
        {
            Brick currentBrick;

            currentBrick._size.height = 0.25f;
            currentBrick._size.width = 0.25f;
            currentBrick._size.length = 0.25f;

            currentBrick._pos.x = leftCoordinate + horisontalStep * brickCountInOneRow;
            currentBrick._pos.y = downCoordinate + verticalStep * RowsCount;
            currentBrick._pos.z = -5.f;
            currentBrick.recallGeometry();
            _bricks.push_back(currentBrick);

            brickCountInOneRow++;
        }
        while(brickCountInOneRow < 5);
        RowsCount++;
    }
    while(RowsCount < 8);

    //init ball
    _myBall.setPossition(_myDeck._pos.x + _myBall._size, _myDeck._pos.y, _myDeck._pos.z);
}

//we need some restrictions for model
bool Game::isCollision(Ball const &currentBall, Brick const &currentBrick) const
{
    //ball above brick
    if (currentBall._pos.y > currentBrick._pos.y + (currentBall._size + currentBrick._size.height / 2.f))
    {
        return false;
    }

    //ball below brick
    if (currentBall._pos.y < currentBrick._pos.y - (currentBall._size + currentBrick._size.height / 2.f))
    {
        return false;
    }

    // ball leftest then brick
    if (currentBall._pos.x > currentBrick._pos.x + (currentBall._size + currentBrick._size.width / 2.f))
    {
        return false;
    }

    // ball rightest then brick
    if (currentBall._pos.x < currentBrick._pos.x - (currentBall._size + currentBrick._size.width / 2.f))
    {
        return false;
    }

    //ball in front of brick
    if (currentBall._pos.z > currentBrick._pos.z + (currentBall._size + currentBrick._size.length / 2.f))
    {
        return false;
    }
    //ball in back from  brick
    if (currentBall._pos.z < currentBrick._pos.z - (currentBall._size + currentBrick._size.length / 2.f))
    {
        return false;
    }

    return true;
}

void Game::changeTrajectory(Ball &currentBall, Brick const &currentBrick, bool const isDeck = false) const
{
    if(!currentBall._isRunning) return;

    //change trajectory
    static const float thickness = 3;

    //right
    if (currentBall._pos.x > currentBrick._pos.x + currentBrick._size.width / thickness)
    {
        currentBall._speed.X = fabs(currentBall._speed.X); // ok
    } 
    //left
    if (currentBall._pos.x < currentBrick._pos.x - currentBrick._size.width / thickness)
    {
        currentBall._speed.X = -fabs(currentBall._speed.X); //ok
    }

    // down 
    if (currentBall._pos.y < currentBrick._pos.y - currentBrick._size.height / thickness)
    {
        currentBall._speed.Y = -fabs(currentBall._speed.Y);
    }
    //up
    if (currentBall._pos.y > currentBrick._pos.y + currentBrick._size.height / thickness)
    {
        currentBall._speed.Y = fabs(currentBall._speed.Y);
    }
    
    // forward
    if (currentBall._pos.z < currentBrick._pos.z - currentBrick._size.length / thickness)
    {
        currentBall._speed.Z = -fabs(currentBall._speed.Z);
    }
    //backward
    if (currentBall._pos.z > currentBrick._pos.z + currentBrick._size.length / thickness)
    {
        currentBall._speed.Z = fabs(currentBall._speed.Z);
    }

    //change angle of ball trajectory
    if(isDeck && currentBall._isRunning)
    {
        currentBall._speed.X = -(currentBrick._pos.x - currentBall._pos.x)*3.f;
      //  currentBall._speed.Z = -(currentBrick._pos.z - currentBall._pos.z)*3.f;
    }
}
//--------------
Game::Game(void)
{
}


Game::~Game(void)
{
}
