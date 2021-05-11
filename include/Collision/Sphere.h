#pragma once

#include "Collision/Collision.h"

class Sphere : public Collision
{
public:
    Sphere(float radius = 0.5f);
    virtual ~Sphere();

    float Radius;
};
