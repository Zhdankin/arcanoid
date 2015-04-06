#include "Brick.h"

Brick::Brick()
{
    _pos.x = 0.f;
    _pos.y = 0.f;
    _pos.z = -5.f;

    _size.height = 0.5f;
    _size.width = 0.5f;
    _size.length = 0.5f;

    for(int i = 0; i < _sides_arr_size; i++)
    {
    _sides_arr[i] = 0.f;
    }
}

Brick::Brick(DimensionPossition const &possition, CuboidSize const &bricksize)
{
    this->Brick::Brick();
    _pos = possition;
    _size = bricksize;
}

void Brick::recallGeometry()
{
    //get vertexes
    const float x = _pos.x;
    const float y = _pos.y;
    const float z = _pos.z;

    const float a = _size.height;
    const float b = _size.width;
    const float c = _size.length;

    const int k = _dimensions;

    const int count_vertex = 8;
    GLfloat ar[count_vertex * _dimensions];

    const char sx[count_vertex] = {'-', '-', '+', '+', '-', '-', '+', '+'};
    const char sy[count_vertex] = {'+', '+', '+', '+', '-', '-', '-', '-'};
    const char sz[count_vertex] = {'+', '-', '-', '+', '+', '-', '-', '+'};
    
    for (int i = 0; i < count_vertex; i++)
    { 
        if (sx[i] == '+') {ar[k * i]     = x + a / 2.f;} else {ar[k * i]     = x - a / 2.f;}
        if (sy[i] == '+') {ar[k * i + 1] = y + b / 2.f;} else {ar[k * i + 1] = y - b / 2.f;}
        if (sz[i] == '+') {ar[k * i + 2] = z + c / 2.f;} else {ar[k * i + 2] = z - c / 2.f;}
    }

    //------------ get sides rect coordinates
    const int index_sides[_index_sides_size] = {
        1,0,4,5,
        0,3,7,4,
        3,2,6,7,
        5,6,2,1,
        1,2,3,0,
        4,7,5,6
    };

    for (int i = 0; i < _index_sides_size; i++  )
    {
        _sides_arr[i * k] = ar[index_sides[i] * k];
        _sides_arr[i * k + 1] = ar[index_sides[i] * k + 1];
        _sides_arr[i * k + 2] = ar[index_sides[i] * k + 2];
    }
}
void Brick::draw() const
{
    //------------ draw
    glColor3f(0.0f, 0.0f, 255.0f);
    glPushMatrix();

    const int k = _dimensions;
    for (int i = 0, c = 0; i < _faces; i += 1, c += 12)
    {
        glBegin(GL_QUADS);
        for (int j = 0; j < _verices; j++)
        {
            glVertex3f(
                _sides_arr[k * j + c], 
                _sides_arr[k * j + c + 1], 
                _sides_arr[k * j + c + 2]);
        }
        glEnd();
    }
    glPopMatrix();
}

Brick::~Brick()
{

}
