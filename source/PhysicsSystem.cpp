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
	vector<RigidbodyComponent *> rigidbodies = EntitySystem::GetInstance()->GetRigidbodyComponentList();
	vector<pair<RigidbodyComponent *, RigidbodyComponent *>> pairs;
	for (unsigned int i = 0; i < rigidbodies.size(); i++)
	{
		RigidbodyComponent *currentRb = rigidbodies[i];
		if (currentRb->isActive)
		{

			guVecScale(&currentRb->force, &currentRb->acceleration, 1 / currentRb->mass);

			//Multiply acceleration by deltatime
			guVector accelerationDeltaTime;
			guVecScale(&currentRb->acceleration, &accelerationDeltaTime, deltaTime);
			guVecAdd(&currentRb->velocity, &accelerationDeltaTime, &currentRb->velocity);

			guVector velocityDeltaTime;
			guVecScale(&currentRb->velocity, &velocityDeltaTime, deltaTime);
			guVecAdd(&currentRb->Owner->Transform.Position, &velocityDeltaTime, &currentRb->Owner->Transform.Position);

			currentRb->force = Maff::VectorZero;
		}
	}
}

PhysicsSystem::~PhysicsSystem() {}
