#pragma once

#include <wiiuse/wpad.h>

#include "SystemBase.h"

class EntitySystem;

class WPadSystem : public SystemBase
{
public:
    static WPadSystem *myInstance;

    WPadSystem();

public:
    static WPadSystem *GetInstance();

    virtual void Init();

    virtual void Update(float deltaTime);

    ~WPadSystem();

    void ScanPad(int PadNumber);

public:


    // Wiimote Infrared Radiation
    ir_t ir;

    WPADData data;
    u16 buttonsHeld;
    u16 buttonsDown;
    u16 buttonsUp;
    u16 wButtonsHeld;
    u16 wButtonsDown;
    u16 wButtonsUp;

public:
    // MEM2 memory allocation routines. The application must provide these to
    // WPAD, so it can setup the data transfer buffer. This buffer must reside
    // in MEM2.
    // static void *myAlloc(u32 size);
    // static u8 myFree(void *ptr);
};