#pragma once

//Forward Declarations
class GameObject;

class Component
{
public:
    Component(){};
    virtual ~Component(){};

    GameObject *Owner;
    bool isDisabled = false;
};
