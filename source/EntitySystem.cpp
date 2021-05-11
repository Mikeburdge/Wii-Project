#include "Systems/EntitySystem.h"

#include "Systems/WPadSystem.h"
#include "Systems/PhysicsSystem.h"
#include "Systems/GraphicsSystem.h"

#include "Components/GameObject.h"
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
		sysGraphics->origin = {0.0F, 0.0F, -1.0F};

		sysGraphics->yaw = 0;
		sysGraphics->pitch = 0;

		// GameObject *coolDog = new GameObject("CoolDog", Maff::VectorZero, Maff::QuaternionIdentity, Maff::VectorOne);
		// coolDog->AddComponent(new MeshComponent("Beagle"));
		// AddObject(coolDog);

		GameObject *whiteBall = new GameObject("WhiteBall", {0, 0, 0}, Maff::QuaternionIdentity, guVector{0.15f, 0.15f, 0.15f});
		whiteBall->AddComponent(new MeshComponent("pool_ball_white"));
		whiteBall->AddComponent(new RigidbodyComponent());

		AddObject(whiteBall);

		// GameObject *dog = new GameObject("Dog", {1, 0, 0}, Maff::QuaternionIdentity, Maff::VectorOne);
		// dog->AddComponent(new MeshComponent("Dog"));
		// AddObject(dog);

		// GameObject *lowpolydog = new GameObject("lowpolydog", {1, 0, 0}, Maff::QuaternionIdentity, Maff::VectorOne);
		// lowpolydog->AddComponent(new MeshComponent("LowPolyDog"));
		// AddObject(lowpolydog);

		GameObject *ball = new GameObject("BallRed", guVector{0, 0, 0}, Maff::QuaternionIdentity, guVector{0.15f, 0.15f, 0.15f});
		ball->AddComponent(new MeshComponent("pool_ball_red"));

		AddObject(ball);

		GameObject *ball2 = new GameObject("BallBlue", guVector{1, 0, 0}, Maff::QuaternionIdentity, guVector{0.15f, 0.15f, 0.15f});
		ball2->AddComponent(new MeshComponent("pool_ball_blue"));

		AddObject(ball2);

		GameObject *ball4 = new GameObject("BallRed2", guVector{1, 1, 0}, guQuaternion{0, 1, 1, 0}, guVector{0.15f, 0.15f, 0.15f});
		ball4->AddComponent(new MeshComponent("pool_ball_red"));

		AddObject(ball4);

		GameObject *ball5 = new GameObject("BallBlue2", guVector{6, -1.0, 0}, Maff::QuaternionIdentity, guVector{0.15f, 0.15f, 0.15f});
		ball5->AddComponent(new MeshComponent("pool_ball_blue"));

		AddObject(ball5);

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