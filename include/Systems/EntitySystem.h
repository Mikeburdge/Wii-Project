#pragma once

#include "SystemBase.h"
#include "Entity.h"

// #include "Components/MeshComponent.h"

#include "SceneID.h"
#include <vector>

//Forward Declarations
class GameObject;
class MeshComponent;
class RigidbodyComponent;

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

    void ClearAllObjects();

    vector<MeshComponent *> GetMeshComponentList();

    vector<RigidbodyComponent *> GetRigidbodyComponentList();

    vector<GameObject *> FullGameObjectList;
};