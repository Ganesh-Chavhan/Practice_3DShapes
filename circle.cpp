#include "circle.h"
#include <cmath>

const float PI = 3.14159f;

Circle::Circle(float radius)
{
    this->radius = radius;
}

QVector<float> Circle::getPoints()
{
    QVector<float> points;
    int pt = 360;

    for (int i = 0; i < pt; i++) {
        float angle = 2.0f * PI * i / pt;

        float x = radius * cos(angle);
        float y = radius * sin(angle);

        // R, G, B color
        float r = 1.0f;
        float g = 0.5f;
        float b = 0.5f;

        points.push_back(x);
        points.push_back(y);
        points.push_back(r);
        points.push_back(g);
        points.push_back(b);
    }

    return points;
}