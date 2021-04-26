#pragma once

//Inherited class
#include "SystemBase.h"

#include <gccore.h>
#include <string>
#include <malloc.h>

#define FRAMEBUFFER_SIZE 2
#define DEFAULT_FIFO_SIZE (1024*1024)

class GraphicsSystem : public SystemBase
{
private:

    static GraphicsSystem* m_instance;

    GraphicsSystem();

public:

    static GraphicsSystem* GetInstance();

    virtual void Init();

    virtual void Update(float deltaTime); 

    ~GraphicsSystem();

    void InitGXVideo();

public:

//Variables

	//Video
	GXRModeObj *videoMode;
	uint32_t *videoFrameBuffer[FRAMEBUFFER_SIZE];
	uint32_t videoFrameBufferIndex;

	//Graphics
	void* gsFifo;
	uint32_t gsWidth;
	uint32_t gsHeight;

	//Matrices - Coordinate spaces
	Mtx m_view, m_model, m_modelview;
	Mtx44 m_projection;
	guVector m_cam, m_up, m_look;
	float m_pitch,m_yaw;
	    
    //Models
	// std::vector<Mesh> m_meshes;

	//Lighting
	GXColor m_background;

	// //Textures
	// TPLFile m_paletteTPL;

};
