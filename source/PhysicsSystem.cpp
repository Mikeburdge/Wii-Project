#include "Systems/PhysicsSystem.h" //Always place corresponding .h first

#include "Statics/Statics.h"

#include <iostream>



using namespace std;

PhysicsSystem::PhysicsSystem(){}

PhysicsSystem* PhysicsSystem::m_instance = 0;

PhysicsSystem* PhysicsSystem::GetInstance()
{
	if (!m_instance)
		m_instance = new PhysicsSystem();
	
    return m_instance;
}

void PhysicsSystem::Init()
{
}

void PhysicsSystem::Update(float deltaTime)
{
}

PhysicsSystem::~PhysicsSystem(){}

