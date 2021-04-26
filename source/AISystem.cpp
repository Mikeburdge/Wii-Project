#include "Systems\AISystem.h"

using namespace std;

AISystem::AISystem(){

}

AISystem* AISystem::m_instance = 0;

AISystem* AISystem::GetInstance()
{
	if (!m_instance)
		m_instance = new AISystem();
	
    return m_instance;
}

void AISystem::Init()
{

}

void AISystem::Update(float deltaTime){
    
}

AISystem::~AISystem(){}