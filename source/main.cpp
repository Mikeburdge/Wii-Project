#include "Systems/EntitySystem.h"
#include "Systems/GraphicsSystem.h"
#include "Systems/PhysicsSystem.h"
#include "Systems/AISystem.h"

//libOGC
#include <gctypes.h>

//Not sure what this is actually doing, just copied it over since the lack of it might fuck things up
#include <DevKitPro/ogc/lwp_watchdog.h>

#include <ostream>
#include <fstream>
#include <iostream>

class SceneID;

using namespace std;

//TODO: LOOK INTO WHETHER I SHOULD HAVE u8 OR float OR u64 for limits 
u8 LOW_LIMIT = 0.0167f;          // Keep At/Below 60fps
u8 HIGH_LIMIT = 0.1f;            // Keep At/Above 10fps

/**
 * Program entry point.
 *
 * @param argc	Number of provided command line parameters.
 * @param argv	List of command line parameters.
 *
 * @return Program exit status code.
 */
int main(int argc, char **argv)
{

//Initializes the VIDEO subsystem
VIDEO_Init();

float lastTime = gettime();

//Calls Initial Functions (apparently, cant find anything what it is)
// __lwp_watchdog_init();

//Singletons:
//Entity
EntitySystem* SysEntity = EntitySystem::GetInstance();
//Graphics
GraphicsSystem* SysGraphics = GraphicsSystem::GetInstance();
//Physics
PhysicsSystem* SysPhysics = PhysicsSystem::GetInstance();
//AI
AISystem* SysAI = AISystem::GetInstance();

//Load the first scene we want to see
SysEntity->LoadScene(SceneID::SceneName::Testing);

  while (true)
  {
      //Keeps track of the current time
      float currentTime = gettime();
      //gets delta time by removing the previous time from current time and dividing by 1000
      float deltaTime = ( currentTime - lastTime ) / 1000.0f;

      //Limits the deltatime to its min and max
      if ( deltaTime < LOW_LIMIT )
        deltaTime = LOW_LIMIT;
      else if ( deltaTime > HIGH_LIMIT )
        deltaTime = HIGH_LIMIT;

      lastTime = currentTime;

      //Update the different systems passign through deltatime
      SysGraphics->Update(deltaTime);
      SysPhysics->Update(deltaTime);
      SysAI->Update(deltaTime);
      SysEntity->Update(deltaTime);
      
      
    

    

    }

    delete SysGraphics;
    delete SysPhysics;
    delete SysAI;
    delete SysEntity;
    
    return 0;
}