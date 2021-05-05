#pragma once

#include "SystemBase.h"
#include "Entity.h"

#include "Components/GameObject.h"

#include "Components/MeshComponent.h"

#include "SceneID.h"

using namespace std;


class EntitySystem : public SystemBase
{
public:
    static EntitySystem *myInstance;

    EntitySystem();

    static EntitySystem *GetInstance();

    ~EntitySystem();

    virtual void Init();

    virtual void Update(float deltaTime);

    void LoadScene(SceneName InScene);

    void AddObject(GameObject *OBJ);

    template <class T>
    vector<T*> GetComponentList();	
    
    std::vector< MeshComponent * > GetMeshComponentList();

    vector<GameObject *> FullGameObjectList;
};