#pragma once

#include "SystemBase.h"

class WPadSystem : public SystemBase
{
public:
    static WPadSystem *myInstance;

    WPadSystem();

public:
    static WPadSystem *GetInstance();

    virtual void Init();

    virtual void Update(float deltaTime);

    ~WPadSystem();
};