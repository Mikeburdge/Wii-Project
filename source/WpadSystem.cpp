#include "Systems/WPadSystem.h"

#include <wiiuse/wpad.h>

//get viewport size
#include "Systems/GraphicsSystem.h"
#include "Systems/EntitySystem.h"

#include "Components/GameObject.h"
#include "Components/TransformComponent.h"
#include "Components/RigidbodyComponent.h"

#include <vector>

using namespace std;

WPadSystem::WPadSystem()
{
    //Retrieve Graphics System
    GraphicsSystem *SysGraphics = GraphicsSystem::GetInstance();

    // I was told you must register allocated and free memory to MEM2
    // before invoking WPADInit() but it is out of scope and unecessary
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

void WPadSystem::Init() {}

void WPadSystem::Update(float deltaTime)
{
    ScanPad(0);

    vector<RigidbodyComponent *> rigidbodies = EntitySystem::GetInstance()->GetRigidbodyComponentList();

    for (unsigned int i = 0; i < rigidbodies.size(); i++)
    {
        RigidbodyComponent *currentRigidbody = rigidbodies[i];
        TransformComponent *transformComp = &currentRigidbody->Owner->Transform;

        if (wButtonsHeld & WPAD_BUTTON_LEFT)
        {
            transformComp->Position.x -= 1;
        }
        if (wButtonsDown & WPAD_BUTTON_LEFT)
        {
            transformComp->Position.x -= 1;
        }
        if (wButtonsHeld & WPAD_BUTTON_RIGHT)
        {
            transformComp->Position.x += 1;
        }
        if (wButtonsDown & WPAD_BUTTON_RIGHT)
        {
            transformComp->Position.x += 1;
        }
        if (wButtonsHeld & WPAD_BUTTON_UP)
        {
            transformComp->Position.y += 1;
        }
        if (wButtonsDown & WPAD_BUTTON_UP)
        {
            transformComp->Position.y += 1;
        }
        if (wButtonsHeld & WPAD_BUTTON_DOWN)
        {
            transformComp->Position.y -= 1;
        }
        if (wButtonsDown & WPAD_BUTTON_DOWN)
        {
            transformComp->Position.y -= 1;
        }

        if (wButtonsDown & WPAD_BUTTON_PLUS)
        {
            transformComp->Scale.y += 1;
        }
        if (wButtonsDown & WPAD_BUTTON_MINUS)
        {
            transformComp->Scale.y -= 1;
        }
    }

    if (wButtonsDown & WPAD_BUTTON_1)
    {
        EntitySystem *sysEntity = EntitySystem::GetInstance();

        sysEntity->LoadScene(SceneName::Testing);
    }

    if (wButtonsDown & WPAD_BUTTON_2)
    {
        EntitySystem *sysEntity = EntitySystem::GetInstance();

        sysEntity->LoadScene(SceneName::Testing2ElectricBoogaloo);
    }

    // IR Movement
    WPAD_IR(0, &ir);
}

void WPadSystem::ScanPad(int PadNumber)
{
    WPAD_ScanPads();
    data = *WPAD_Data(0);
    wButtonsHeld = data.btns_h;
    wButtonsDown = data.btns_d;
    wButtonsUp = data.btns_u;
}

WPadSystem::~WPadSystem() {}