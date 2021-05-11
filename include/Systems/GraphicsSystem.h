#pragma once

//Inherited class
#include "SystemBase.h"

#include "Components/MeshComponent.h"

#include <vector>
#include <gccore.h>
#include <string>
#include <malloc.h>

#define FRAMEBUFFER_SIZE 2
#define DEFAULT_FIFO_SIZE (1024 * 1024)

struct Mesh
{
	std::string name;
	std::vector<guVector> vertices;
	std::vector<guVector> uvs;
	std::vector<guVector> normals;
};

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

	void SetLight();

	bool LoadMeshFromObj(std::string name, void *fileStream, unsigned int fileSize);

	void DrawMeshes(vector<MeshComponent *> meshes);

	//Called at the end of each frame
	void EndFrame();

public:
	GXRModeObj *videoMode;
	uint32_t *videoFrameBuffer[FRAMEBUFFER_SIZE];
	uint32_t videoFrameBufferIndex;

public:

	void *gsFifo;
	uint32_t gsWidth;
	uint32_t gsHeight;

public:
	//Matrices - Coordinate spaces
	Mtx view, model, modelview;
	Mtx44 projection;
	guVector camPt, up, look;
	float pitch, yaw;

public:
	//Temp Rotation variable
	u32 rot;

public:
	//All Meshes that should be displayed
	std::vector<Mesh> meshCollection;

public:

	GXColor lightColor[2];
	GXColor background;

public:
	TPLFile paletteTPL;
	GXTexObj paletteTexture;

};