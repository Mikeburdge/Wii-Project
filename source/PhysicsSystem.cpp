#include "Systems/PhysicsSystem.h" //Always place corresponding .h first
#include "Systems/EntitySystem.h"

#include "Components/RigidbodyComponent.h"
#include "Components/TransformComponent.h"
#include "Components/GameObject.h"

#include "Collision/Sphere.h"

#include "Utility/Maff.h"

#include "Utility/Statics.h"

#include <iostream>

using namespace std;

PhysicsSystem::PhysicsSystem() {}

PhysicsSystem *PhysicsSystem::myInstance = 0;

PhysicsSystem *PhysicsSystem::GetInstance()
{
	if (!myInstance)
		myInstance = new PhysicsSystem();

	return myInstance;
}

void PhysicsSystem::Init()
{
}

void PhysicsSystem::Update(float deltaTime)
{
	// EntitySystem *sysEntity = EntitySystem::GetInstance();

	// GameObject *DogObject = sysEntity->FindObjectByName("BigDog");

	// if (DogObject)
	// {
	// 	DogObject->Transform.Rotation.y += 1;

	// 	if (DogObject->Transform.Rotation.y > 360.0f)
	// 		DogObject->Transform.Rotation.y -= 360.0f;
	// }
}

PhysicsSystem::~PhysicsSystem() {}
