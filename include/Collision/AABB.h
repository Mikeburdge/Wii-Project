#pragma once

#include "Collision/Collision.h"

class AABB : public Collision
{
public:
    AABB(int inX = 0, int inY = 0, int inWidth = 1, int inHeight = 1) : x(inX), y(inY), width(inWidth), height(inHeight) {};
    virtual ~AABB();

    int x = 5;
    int y = 5;
    int width = 50;
    int height = 50;
};
