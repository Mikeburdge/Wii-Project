#pragma once

#include <string>
#include <vector>

#include "Components/Component.h"

#include "Utility/Maff.h"

//Forward Declarations
class Component;

class GameObject
{
public:
    GameObject(std::string objectName = "Default GameObject", guVector position = Maff::VectorZero, guQuaternion rotation = Maff::QuaternionIdentity, guVector scale = Maff::VectorOne);

    ~GameObject();

    void AddComponent(Component *inComp);

    /**
 * @brief Use this to find a component within the gameobjects @see subComponents
 * 
 * @note This will always return the first component of type T found
 * 
 * @tparam T The class in which the function searches for
 * @return T If successful returns a class of type T, if unsuccessful returns nullptr
 */
    template <class T>
    T* FindComponent();

    std::vector<Component *> subComponents;
};
