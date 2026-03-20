#include "cube.h"

Cube::Cube(float size)
{
    this->size = size;
}

QVector<float> Cube::getPoints()
{
    float s = size;

    // A cube has 12 edges total

    QVector<float> points = {

        // front face (z = +s) — red
        -s, -s, +s,   1,0,0,    +s, -s, +s,   1,0,0,  // bottom edge
        +s, -s, +s,   1,0,0,    +s, +s, +s,   1,0,0,  // right edge
        +s, +s, +s,   1,0,0,    -s, +s, +s,   1,0,0,  // top edge
        -s, +s, +s,   1,0,0,    -s, -s, +s,   1,0,0,  // left edge

        // back face (z = -s) — blue
        -s, -s, -s,   0,0,1,    +s, -s, -s,   0,0,1,
        +s, -s, -s,   0,0,1,    +s, +s, -s,   0,0,1,
        +s, +s, -s,   0,0,1,    -s, +s, -s,   0,0,1,
        -s, +s, -s,   0,0,1,    -s, -s, -s,   0,0,1,

        // connecting edges front to back — green
        -s, -s, +s,   0,1,0,    -s, -s, -s,   0,1,0,
        +s, -s, +s,   0,1,0,    +s, -s, -s,   0,1,0,
        +s, +s, +s,   0,1,0,    +s, +s, -s,   0,1,0,
        -s, +s, +s,   0,1,0,    -s, +s, -s,   0,1,0,
    };

    return points;
}