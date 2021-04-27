#pragma once

//Inherited class
#include "SystemBase.h"

#include <gccore.h>
#include <string>
#include <malloc.h>

#define FRAMEBUFFER_SIZE 2
#define DEFAULT_FIFO_SIZE (1024 * 1024)

class GraphicsSystem : public SystemBase
{
private:
	static GraphicsSystem *myInstance;

	GraphicsSystem();

public:
	static GraphicsSystem *GetInstance();

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
	void *gsFifo;
	uint32_t gsWidth;
	uint32_t gsHeight;

	//Matrices - Coordinate spaces
	Mtx view, model, modelview;
	Mtx44 projection;
	guVector camera, up, look;
	float pitch, yaw;

	//Models
	// std::vector<Mesh> m_meshes;

	//Lighting
	GXColor background;

	// //Textures
	// TPLFile m_paletteTPL;

	//draw lines and box
	void DrawHLine(int x1, int x2, int y, int color);
	void DrawVLine(int x, int y1, int y2, int color);

	void DrawBox(int x1, int y1, int x2, int y2, int color);
public:
	//Called at the end of each frame
	void EndFrame();
};
