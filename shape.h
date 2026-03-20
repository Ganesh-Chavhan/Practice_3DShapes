#pragma once

#include <QVector>

class Shape
{
public:
    virtual QVector<float> getPoints() = 0;

    virtual ~Shape() {}
};