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

void EntitySystem::LoadScene(SceneID::SceneName InScene)
{
	switch (InScene)
	{
	case SceneID::SceneName::Starting:
		/* code */
		break;

	case SceneID::SceneName::Testing:
	{
		GameObject *coolDog = new GameObject("CoolDog", Maff::VectorZero, Maff::QuaternionIdentity, Maff::VectorOne);

		AddObject(coolDog);

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
T *EntitySystem::GetComponentList()
{
	vector<T *> templateList;

	for (u16 i = 0; i < FullGameObjectList.size(); i++)
	{
		GameObject *currentObject = FullGameObjectList[i];

		for (u16 j = 0; j < currentObject->subComponents.size(); j++)
		{
			T *tempComp = dynamic_cast<T *>(currentObject->subComponents[j]);

			if (tempComp && !tempComp->isDisabled)
			{
				templateList.push_back(tempComp);
			}
		}
	}

	return nullptr;
}