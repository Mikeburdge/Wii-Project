#include "Systems/EntitySystem.h"

#include "Systems/WPadSystem.h"
#include "Systems/PhysicsSystem.h"
#include "Systems/GraphicsSystem.h"

#include "Components/RigidbodyComponent.h"

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
	WPadSystem *sysWPad = WPadSystem::GetInstance();
	PhysicsSystem *sysPhysics = PhysicsSystem::GetInstance();
	GraphicsSystem *sysGraphics = GraphicsSystem::GetInstance();

	ClearAllObjects();

	switch (InScene)
	{
	case SceneName::Starting:
		/* code */
		break;

	case SceneName::Testing:
	{
		//Re initiating the projection values
		sysGraphics->camPt = {0.0F, 0.0F, 0.0F};
		sysGraphics->up = {0.0F, 1.0F, 0.0F};
		sysGraphics->look = {0.0F, 0.0F, -1.0F};

		sysGraphics->yaw = 0;
		sysGraphics->pitch = 0;

		GameObject *whiteBall = new GameObject("WhiteBall", guVector{10, 0, 0});
		whiteBall->AddComponent(new MeshComponent("WhiteBallMesh"));
		whiteBall->AddComponent(new RigidbodyComponent(0.5f, 1.0f, false, false));
		AddObject(whiteBall);

		GameObject *whiteBall2 = new GameObject("WhiteBall2", guVector{-10, 0, 0});
		whiteBall2->AddComponent(new MeshComponent("WhiteBallMesh"));
		whiteBall2->AddComponent(new RigidbodyComponent(0.5f, 1.0f, false, false));
		AddObject(whiteBall2);

		// GameObject *DogOnlineConverter = new GameObject("DogOnlineConverter", guVector{1, 0, 0});
		// DogOnlineConverter->AddComponent(new MeshComponent("DogOnlineConverterMesh"));
		// DogOnlineConverter->AddComponent(new RigidbodyComponent(0.5f, 1.0f, false, false));
		// AddObject(DogOnlineConverter);

		// GameObject *WillDog = new GameObject("WillDog", guVector{1, 0, 0});
		// WillDog->AddComponent(new MeshComponent("WillDogMesh"));
		// WillDog->AddComponent(new RigidbodyComponent(0.5f, 1.0f, false, false));
		// AddObject(WillDog);

		// GameObject *GreenGoblinMask = new GameObject("GreenGoblinMask");
		// GreenGoblinMask->AddComponent(new MeshComponent("GreenGoblinMaskMesh"));
		// GreenGoblinMask->AddComponent(new RigidbodyComponent(0.5f, 1.0f, false, false));

		// AddObject(GreenGoblinMask);

		break;
	}

	case SceneName::Testing2ElectricBoogaloo:
	{

		GameObject *dog = new GameObject("BigDog", {0, 0, 0}, Maff::QuaternionIdentity, Maff::VectorOne);
		dog->AddComponent(new MeshComponent("DogMesh"));
		AddObject(dog);

		break;
	}

	default:
		break;
	}

	//Reinitialise all systems after loading a new scene
	//(unless i can think of something to put in the inits this is useless)
	this->Init();
	sysWPad->Init();
	sysPhysics->Init();
	sysGraphics->Init();
}

void EntitySystem::AddObject(GameObject *inOBJ)
{
	FullGameObjectList.push_back(inOBJ);
}

void EntitySystem::ClearAllObjects()
{
	for (GameObject *obj : FullGameObjectList)
		delete obj;

	FullGameObjectList.clear();
}

GameObject *EntitySystem::FindObjectByName(string name)
{
	GameObject *returnedObj = nullptr;
	for (u16 i = 0; i < FullGameObjectList.size(); i++)
	{
		if (FullGameObjectList[i]->Name.compare(name) == 0)
		{
			returnedObj = FullGameObjectList[i];
		}
	}
	return returnedObj;
}

std::vector<MeshComponent *> EntitySystem::GetMeshComponentList()
{
	std::vector<MeshComponent *> compList;

	for (u16 i = 0; i < FullGameObjectList.size(); i++)
	{
		GameObject *currentObject = FullGameObjectList[i];

		for (u16 j = 0; j < currentObject->SubComponents.size(); j++)
		{
			MeshComponent *tempComp = dynamic_cast<MeshComponent *>(currentObject->SubComponents[j]);

			if (tempComp && !tempComp->isDisabled)
			{
				compList.push_back(tempComp);
			}
		}
	}

	return compList;
}

std::vector<RigidbodyComponent *> EntitySystem::GetRigidbodyComponentList()
{
	std::vector<RigidbodyComponent *> compList;

	for (u16 i = 0; i < FullGameObjectList.size(); i++)
	{
		GameObject *currentObject = FullGameObjectList[i];

		for (u16 j = 0; j < currentObject->SubComponents.size(); j++)
		{
			RigidbodyComponent *tempComp = dynamic_cast<RigidbodyComponent *>(currentObject->SubComponents[j]);

			if (tempComp && !tempComp->isDisabled)
			{
				compList.push_back(tempComp);
			}
		}
	}

	return compList;
}