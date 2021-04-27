#include "Systems\WpadSystem.h"

#include <wiiuse\wpad.h>

//get viewport size
#include "Systems\GraphicsSystem.h"

using namespace std;

WpadSystem::WpadSystem()
{
//Graphics
GraphicsSystem* SysGraphics = GraphicsSystem::GetInstance();

    
	WPAD_Init();
	WPAD_SetVRes(0, SysGraphics->gsWidth, SysGraphics->gsHeight);
	WPAD_SetDataFormat(WPAD_CHAN_0, WPAD_FMT_BTNS_ACC_IR);  

}

WpadSystem* WpadSystem::myInstance = 0;

WpadSystem* WpadSystem::GetInstance()
{
	if (!myInstance)
		myInstance = new WpadSystem();
	
    return myInstance;
}

void WpadSystem::Init()
{

}

void WpadSystem::Update(float deltaTime){
    
}



WpadSystem::~WpadSystem(){}