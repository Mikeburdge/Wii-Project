#pragma once

//Forward Declarations
class GameObject;

class Component
{
private:
    /* data */
public:
    Component(){};
    virtual ~Component(){};

    GameObject *Owner;
    bool isDisabled = false;
};
