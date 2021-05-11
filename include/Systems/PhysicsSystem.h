#pragma once

#include "SystemBase.h"

#include "stdio.h"

#include <iostream>

class RigidbodyComponent;
class Sphere;

using namespace std;

class PhysicsSystem : public SystemBase
{
public:
    static PhysicsSystem *myInstance;

    PhysicsSystem();

    static PhysicsSystem *GetInstance();

    virtual void Init();

    virtual void Update(float deltaTime);

    ~PhysicsSystem();


    float Gravity;
    float AirViscosity;
    float FrictionCoefficient;
};