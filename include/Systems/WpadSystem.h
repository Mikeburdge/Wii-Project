#pragma once

#include "SystemBase.h"

class WpadSystem : public SystemBase
{
public:
    static WpadSystem *myInstance;

    WpadSystem();

public:
    static WpadSystem *GetInstance();

    virtual void Init();

    virtual void Update(float deltaTime);

    ~WpadSystem();
};