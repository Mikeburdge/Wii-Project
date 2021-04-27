#pragma once

#include "SystemBase.h"

class AISystem : public SystemBase
{
public:

    static AISystem* myInstance;

    AISystem();

public:

    static AISystem* GetInstance();

    virtual void Init();

    virtual void Update(float deltaTime); 

    ~AISystem();

};