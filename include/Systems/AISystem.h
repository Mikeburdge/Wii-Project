#ifndef AISYSTEM_H_
#define AISYSTEM_H_

#include "SystemBase.h"

class AISystem : public SystemBase
{
public:

    static AISystem* m_instance;

    AISystem();

public:

    static AISystem* GetInstance();

    virtual void Init();

    virtual void Update(float deltaTime); 

    ~AISystem();

};

#endif /*AISYSTEM_H_*/