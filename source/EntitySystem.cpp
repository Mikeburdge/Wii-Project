#include "Systems/EntitySystem.h"

EntitySystem::EntitySystem() {}

EntitySystem::~EntitySystem() {}

EntitySystem *EntitySystem::myInstance = 0;

EntitySystem *EntitySystem::GetInstance()
{
	if (!myInstance)
		myInstance = new EntitySystem();

	return myInstance;
}

void EntitySystem::Init()
{
}

void EntitySystem::Update(float deltaTime)
{
}

void EntitySystem::LoadScene(SceneName InScene)
{
	switch (InScene)
	{
	case SceneName::Starting:
		/* code */
		break;

	case SceneName::Testing:
	{
		GameObject *coolDog = new GameObject("CoolDog", Maff::VectorZero, Maff::QuaternionIdentity, Maff::VectorOne);
		coolDog->AddComponent(new MeshComponent("cooldog"));

		AddObject(coolDog);

		GameObject *whiteBall = new GameObject("WhiteBall", {0, 1, 0}, Maff::QuaternionIdentity, Maff::VectorOne);
		whiteBall->AddComponent(new MeshComponent("whiteball"));

		break;
	}

	default:
		break;
	}
}

void EntitySystem::AddObject(GameObject *inOBJ)
{
	FullGameObjectList.push_back(inOBJ);
}

template <class T>
vector<T *> EntitySystem::GetComponentList()
{
	vector<T *> compList;

	for (u16 i = 0; i < FullGameObjectList.size(); i++)
	{
		GameObject *currentObject = FullGameObjectList[i];

		for (u16 j = 0; j < currentObject->SubComponents.size(); j++)
		{
			T *tempComp = dynamic_cast<T *>(currentObject->SubComponents[j]);

			if (tempComp && !tempComp->isDisabled)
			{
				compList.push_back(tempComp);
			}
		}
	}

	return nullptr;
}

//Model meshes
std::vector<MeshComponent *> EntitySystem::GetMeshComponentList()
{
	//Iterate through gameobjects, find MeshComponents through i.e dynamic_casts
	//Add pointers to such meshcomponents to the vector, return such vector
	std::vector<MeshComponent *> meshCompList;
	//@Beware of vectors dynamically moving instances in memory
	for (u16 i = 0; i < FullGameObjectList.size(); i++)
	{
		GameObject *curObj = FullGameObjectList[i];
		//Find mesh components
		for (u16 j = 0; j < curObj->SubComponents.size(); j++)
		{
			//Dynamic casting to identify type;
			MeshComponent *meshComp = dynamic_cast<MeshComponent *>(curObj->SubComponents[j]);
			if (meshComp && !meshComp->isDisabled)
			{
				meshCompList.push_back(meshComp);
			}
		}
	}
	return meshCompList;
}