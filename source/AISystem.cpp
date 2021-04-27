#include "Systems\AISystem.h"

using namespace std;

AISystem::AISystem(){

}

AISystem* AISystem::myInstance = 0;

AISystem* AISystem::GetInstance()
{
	if (!myInstance)
		myInstance = new AISystem();
	
    return myInstance;
}

void AISystem::Init()
{

}

void AISystem::Update(float deltaTime){
    
}

AISystem::~AISystem(){}