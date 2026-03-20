#pragma once

#include "shape.h"
#include<QVector>

class Cube : public Shape
{
public:
    Cube(float size);
    QVector<float> getPoints() override;

private:
    float size;
};

