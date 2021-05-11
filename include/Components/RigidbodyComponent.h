#pragma once

#include "Components/Component.h"

#include "Collision/Collision.h"

#include "ogc/gu.h"

class RigidbodyComponent : public Component
{
public:
    RigidbodyComponent(float inRadius = 0.5f, float inMass = 1.f, bool isKinematic = false, bool isTrigger = false);

    ~RigidbodyComponent(){};

    Collision *collision;
    float mass;
    bool isKinematic;
    bool isTrigger;
    bool isActive;

    guVector force;
    guVector acceleration;
    guVector velocity;
};
