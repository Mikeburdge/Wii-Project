#include "Systems/WPadSystem.h"

#include <wiiuse/wpad.h>

//get viewport size
#include "Systems/GraphicsSystem.h"

using namespace std;

WPadSystem::WPadSystem()
{
    //Retrieve Graphics System
    GraphicsSystem *SysGraphics = GraphicsSystem::GetInstance();

    // I was told you must register allocated and free memory to MEM2 before invoking WPADInit() but it is out of scope and unecessary
    // WPADRegisterAllocator(myAlloc, myFree);

    WPAD_Init();

    WPAD_SetVRes(0, SysGraphics->gsWidth, SysGraphics->gsHeight);
    WPAD_SetDataFormat(WPAD_CHAN_0, WPAD_FMT_BTNS_ACC_IR);
}

WPadSystem *WPadSystem::myInstance = 0;

WPadSystem *WPadSystem::GetInstance()
{
    if (!myInstance)
        myInstance = new WPadSystem();

    return myInstance;
}

void WPadSystem::Init()
{
}

void WPadSystem::Update(float deltaTime)
{

    WPAD_ScanPads();

    //check if buttons are down
    // u32 pressed = WPAD_ButtonsDown(0);

    // IR Movement
    WPAD_IR(0, &ir);
}

WPadSystem::~WPadSystem() {}