#pragma once

#include "shape.h"
#include <QVector>

class Ellipse : public Shape
{
public:
    Ellipse(float rx, float ry);   
    QVector<float> getPoints() override;;

private:
    float rx;   
    float ry;   
};

