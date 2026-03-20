#pragma once
#include "shape.h"
#include <QVector>

class Circle : public Shape
{
public:
    Circle(float radius);
    QVector<float> getPoints() override;

private:
    float radius;
};