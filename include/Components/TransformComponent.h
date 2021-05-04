#pragma once

#include "Components/Component.h"

#include "Utility/Maff.h"
#include "ogc/gu.h"

class TransformComponent
{
public:
    TransformComponent(guVector position = Maff::VectorZero, guQuaternion rotation = Maff::QuaternionIdentity, guVector scale = Maff::VectorOne);

    ~TransformComponent();

    guVector Position;
    guQuaternion Rotation;
    guVector Scale;
};
