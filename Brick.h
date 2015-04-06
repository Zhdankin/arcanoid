#pragma once
#include "Structs.h"
#include <glut.h>

class Brick
{
protected:
    static const int _dimensions = 3;
    // 6 faces on 4 vertices's
    static const int _faces = 6;
    static const int _verices = 4;
    static const int _index_sides_size = _faces * _verices; 
    static const int _sides_arr_size = _index_sides_size * 3; // 3 dimensions
    float _sides_arr[_sides_arr_size];
    DimensionPossition _pos;
    CuboidSize _size;

protected:
    void recallGeometry();

public:
    friend class Game;
    Brick();
    Brick(DimensionPossition const &possition, CuboidSize const &bricksize);
    virtual ~Brick();
    void draw() const;
};
