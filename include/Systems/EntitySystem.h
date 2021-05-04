#pragma once

#include "SystemBase.h"
#include "Entity.h"

#include "Components/GameObject.h"

#include "SceneID.h"

using namespace std;

//Forward Declarations
class SceneID;

class EntitySystem : public SystemBase
{
public:
    static EntitySystem *myInstance;

    EntitySystem();

    static EntitySystem *GetInstance();

    ~EntitySystem();

    virtual void Init();

    virtual void Update(float deltaTime);

    void LoadScene(SceneID::SceneName InScene);

    void AddObject(GameObject *OBJ);

    template <class T>
    T* GetComponentList();

    vector<GameObject *> FullGameObjectList;
};