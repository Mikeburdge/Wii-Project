#include "Systems/PhysicsSystem.h" //Always place corresponding .h first

#include "Utility/Statics.h"

#include <iostream>



using namespace std;

PhysicsSystem::PhysicsSystem(){}

PhysicsSystem* PhysicsSystem::myInstance = 0;

PhysicsSystem* PhysicsSystem::GetInstance()
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
}

PhysicsSystem::~PhysicsSystem(){}

