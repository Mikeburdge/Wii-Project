#pragma once

#include "Components/GameObject.h"

//Forward Declarations
class GameObject;

class Component
{
private:
    /* data */
public:
    Component();
    ~Component();

    GameObject *owner;
    bool isDisabled = false;
};
