#include "Systems/EntitySystem.h"

using namespace std;

EntitySystem::EntitySystem(){}

EntitySystem::~EntitySystem(){}

EntitySystem* EntitySystem::m_instance = 0;

EntitySystem* EntitySystem::GetInstance()
{
	if (!m_instance)
		m_instance = new EntitySystem();
	
    return m_instance;
}

void EntitySystem::Init()
{

}

void EntitySystem::Update(float deltaTime){
    
}

void EntitySystem::LoadScene(SceneID::SceneName InScene){
	switch (InScene)
	{
	case SceneID::SceneName::Starting:
		/* code */
		break;

	case SceneID::SceneName::Testing:
		/* code */
		break;
	
	default:
		break;
	}
}
