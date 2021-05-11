#pragma once

enum CollisionType
{
    SPHERE,
    AABB
};

class Collision
{

public:
    Collision(){};
    virtual ~Collision(){};

    CollisionType collisionType;
};
