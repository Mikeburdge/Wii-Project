#pragma once

#include "SystemBase.h"
#include "Entity.h"

#include "SceneID.h"
//Forward Declare SceneID
class SceneID;

class EntitySystem : public SystemBase
{
public:

    static EntitySystem* myInstance;

    EntitySystem();

    static EntitySystem* GetInstance();

    ~EntitySystem();

    virtual void Init();

    virtual void Update(float deltaTime); 

    void LoadScene(SceneID::SceneName InScene);

};