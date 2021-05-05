#pragma once


#include "Components/Component.h"
#include "Components/TransformComponent.h"

#include <string>
#include <vector>

#include "Utility/Maff.h"

//Forward Declarations
class Component;

class GameObject
{
public:
    GameObject(std::string objectName = "Default Name", guVector position = Maff::VectorZero, guQuaternion rotation = Maff::QuaternionIdentity, guVector scale = Maff::VectorOne);

    ~GameObject();

    void AddComponent(Component *inComp);

    /**
     * @brief Use this to find a component within the gameobjects @see SubComponents
     * 
     * @note This will always return the first component of type T found
     * 
     * @tparam T The class in which the function searches for
     * @return T If successful returns a class of type T, if unsuccessful returns nullptr
     */
    template <class T>
    T *FindComponent();


    TransformComponent Transform;

    std::vector<Component *> SubComponents;
};
