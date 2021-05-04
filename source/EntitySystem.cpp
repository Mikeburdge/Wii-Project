#include "Systems/EntitySystem.h"

using namespace std;

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
	}
	break;

	default:
		break;
	}
}
