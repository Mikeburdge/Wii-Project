#pragma once

#include <string>

#include "Components/Component.h"

#include "Utility/Maff.h"

//Forward Declarations
class Component;

class GameObject
{
public:
    GameObject(std::string objectName = "Default GameObject", guVector position = {0, 0, 0}, guQuaternion rotation = Maff::QuaternionIdentity, guVector scale = Maff::VectorOne);

    ~GameObject();

    void AddComponent(Component *inComp);
};
