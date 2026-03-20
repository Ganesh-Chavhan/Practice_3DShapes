#include "ellipse.h"
#include <cmath>

const float PI = 3.14159f;

Ellipse::Ellipse(float rx, float ry)
{
    this->rx = rx;
    this->ry = ry;
}

QVector<float> Ellipse::getPoints()
{
    QVector<float> points;
    int segments = 100;

    for (int i = 0; i < segments; i++) {
        float angle = 2.0f * PI * i / segments;

        float x = rx * cos(angle);
        float y = ry * sin(angle);

        float r = 0.0f;
        float g = 1.0f;
        float b = 0.5f;

        points.push_back(x);
        points.push_back(y);
        points.push_back(r);
        points.push_back(g);
        points.push_back(b);
    }

    return points;
}