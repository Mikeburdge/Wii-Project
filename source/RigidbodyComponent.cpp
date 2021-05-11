#include "Components/RigidbodyComponent.h"

#include "Collision/Sphere.h"

RigidbodyComponent::RigidbodyComponent(float inRadius, float inMass, bool isKinematic, bool isTrigger)
    : mass(inMass), isKinematic(isKinematic), isTrigger(isTrigger), isActive(true)
{
    collision = new Sphere(inRadius);
    force = {0, 0, 0};
    acceleration = {0, 0, 0};
    velocity = {0, 0, 0};
};