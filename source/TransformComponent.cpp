#include "Components/TransformComponent.h"

TransformComponent::TransformComponent(guVector inPosition, guQuaternion inRotation, guVector inScale)
    : Position(inPosition), Rotation(inRotation), Scale(inScale) {}

TransformComponent::~TransformComponent()
{
}
