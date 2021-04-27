#include "Systems/WPadSystem.h"

#include <wiiuse/wpad.h>

//get viewport size
#include "Systems/GraphicsSystem.h"

using namespace std;

// MEM2 memory allocation routines. The application must provide these to
// WPAD, so it can setup the data transfer buffer. This buffer must reside
// in MEM2.
static void *myAlloc(u32 size);
static u8 myFree(void *ptr);

WPadSystem::WPadSystem()
{
    WPADRegisterAllocator(myAloc, myFree);
    //Graphics
    GraphicsSystem *SysGraphics = GraphicsSystem::GetInstance();

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
}

WPadSystem::~WPadSystem() {}