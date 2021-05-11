#include "Systems/GraphicsSystem.h"

#include "Systems/EntitySystem.h"

#include "Components/GameObject.h"
#include "Components/TransformComponent.h"

#include <stdio.h>
#include <vector>

//Models To Load
#include "GeoSphere_obj.h"
#include "GreenGoblinMask_obj.h"
#include "DogOnlineConverter_obj.h"
#include "WillDog_obj.h"

#include "Beagle_obj.h"
#include "Dog_obj.h"
#include "LowPolyDog_obj.h"
#include "pool_ball_white_obj.h"

#include "pool_ball_red_obj.h"
#include "pool_ball_blue_obj.h"

#include <string.h>
#include "ogc/gu.h"

//Textures
#include "palette_tpl.h"
#include "palette.h"

using namespace std;

GraphicsSystem *GraphicsSystem::myInstance = 0;

GraphicsSystem *GraphicsSystem::GetInstance()
{
	if (!myInstance)
	{
		myInstance = new GraphicsSystem();
	}
	return myInstance;
}

GraphicsSystem::GraphicsSystem()
{
	background = {80, 80, 255, 0};
	camPt = {0.0F, 0.0F, 0.0F};
	up = {0.0F, 1.0F, 0.0F};
	look = {0.0F, 0.0F, -1.0F};

	pitch = 0;
	yaw = 0;

	lightColor[0] = {255, 255, 255, 255};
	lightColor[1] = {150, 150, 150, 255};

	videoFrameBufferIndex = 0;

	//Models to include in the game

	if (!LoadMeshFromObj("WhiteBallMesh", (void *)pool_ball_white_obj, pool_ball_white_obj_size))
		exit(0);
	// if (!LoadMeshFromObj("DogMesh", (void *)Dog_obj, Dog_obj_size))
	// 	exit(0);
	// if (!LoadMeshFromObj("DogOnlineConverterMesh", (void *)DogOnlineConverter_obj, DogOnlineConverter_obj_size))
	// 	exit(0);

	// if (!LoadMeshFromObj("WillDog", (void *)WillDog_obj, WillDog_obj_size))
	// 	exit(0);
	// if (!LoadMeshFromObj("LowPolyDog_obj", (void *)LowPolyDog_obj, LowPolyDog_obj_size))
	// 	exit(0);

	// if (!LoadMeshFromObj("pool_ball_red", (void *)pool_ball_red_obj, pool_ball_red_obj_size))
	// 	exit(0);
	// if (!LoadMeshFromObj("pool_ball_blue", (void *)pool_ball_blue_obj, pool_ball_blue_obj_size))
	// 	exit(0);

	// if (!LoadMeshFromObj("GeoSphereMesh", (void *)GeoSphere_obj, GeoSphere_obj_size))
	// 	exit(0);

	// if (!LoadMeshFromObj("GreenGoblinMaskMesh", (void *)GreenGoblinMask_obj, GreenGoblinMask_obj_size))
	// 	exit(0);

	//Initialises the video
	InitGXVideo();
}

GraphicsSystem::~GraphicsSystem() {}

void GraphicsSystem::Init() {}

void GraphicsSystem::Update(float deltaTime)
{
	//Create a viewing matrix
	guLookAt(view, &camPt, &up, &look);

	//Update Lighting
	SetLight();

	EntitySystem *sysEntity = EntitySystem::GetInstance();

	//Draw
	DrawMeshes(sysEntity->GetMeshComponentList(), deltaTime);

	//Call last each frame
	EndFrame();
}

void GraphicsSystem::InitGXVideo()
{
	VIDEO_Init();

	videoMode = VIDEO_GetPreferredMode(NULL);

	for (uint8_t videoIndex = 0; videoIndex < FRAMEBUFFER_SIZE; videoIndex++)
	{
		videoFrameBuffer[videoIndex] = (uint32_t *)MEM_K0_TO_K1(SYS_AllocateFramebuffer(videoMode));
		VIDEO_ClearFrameBuffer(videoMode, videoFrameBuffer[videoIndex], COLOR_BLACK);
	}
	videoFrameBufferIndex = 0;

	VIDEO_Configure(videoMode);
	VIDEO_SetNextFramebuffer(videoFrameBuffer[videoFrameBufferIndex]);
	VIDEO_SetBlack(FALSE);
	VIDEO_Flush();
	VIDEO_WaitVSync();

	if (videoMode->viTVMode & VI_NON_INTERLACE)
	{
		VIDEO_WaitVSync();
	}

	// allocate the firtst in first out buffer Initializing the GX system
	gsFifo = memalign(32, DEFAULT_FIFO_SIZE);
	memset(gsFifo, 0, DEFAULT_FIFO_SIZE);
	GX_Init(gsFifo, DEFAULT_FIFO_SIZE);

	// Set the background clear color
	GX_SetCopyClear(background, 0x00ffffff);

	// Setup the viewport display
	f32 yscale = GX_GetYScaleFactor(videoMode->efbHeight, videoMode->xfbHeight);
	uint32_t xfbHeight = GX_SetDispCopyYScale(yscale);

	GX_SetViewport(0, 0, videoMode->fbWidth, videoMode->efbHeight, 0, 1);
	GX_SetScissor(0, 0, videoMode->fbWidth, videoMode->efbHeight);
	GX_SetDispCopySrc(0, 0, videoMode->fbWidth, videoMode->efbHeight);
	GX_SetDispCopyDst(videoMode->fbWidth, xfbHeight);
	GX_SetCopyFilter(videoMode->aa, videoMode->sample_pattern, GX_TRUE, videoMode->vfilter);

	// Store graphics system width and height
	gsWidth = (uint32_t)videoMode->fbWidth;
	gsHeight = (uint32_t)videoMode->efbHeight;

	GX_SetFieldMode(videoMode->field_rendering, ((videoMode->viHeight == 2 * videoMode->xfbHeight) ? GX_ENABLE : GX_DISABLE));

	// Anti-aliasing initialization
	if (videoMode->aa)
	{
		GX_SetPixelFmt(GX_PF_RGB565_Z16, GX_ZC_LINEAR);
	}
	else
	{
		GX_SetPixelFmt(GX_PF_RGB8_Z24, GX_ZC_LINEAR);
	}

	GX_SetCullMode(GX_CULL_NONE);
	GX_CopyDisp(videoFrameBuffer[videoFrameBufferIndex], GX_TRUE);
	GX_SetDispCopyGamma(GX_GM_1_0);
	// Texture vertex format setup
	GX_ClearVtxDesc();

	GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XY, GX_F32, 0);
	GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
	GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);

	GX_SetVtxAttrFmt(GX_VTXFMT1, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
	GX_SetVtxAttrFmt(GX_VTXFMT1, GX_VA_NRM, GX_NRM_XYZ, GX_F32, 0);
	GX_SetVtxAttrFmt(GX_VTXFMT1, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);

	// set number of rasterized color channels
	GX_SetNumChans(1);

	//set number of textures to generate
	GX_SetNumTexGens(1);

	//Invalidates the vertex cache and current texture memory cache
	GX_InvVtxCache();
	GX_InvalidateTexAll();
	//Load palette.bmp texture
	TPL_OpenTPLFromMemory(&paletteTPL, (void *)palette_tpl, palette_tpl_size);
	TPL_GetTexture(&paletteTPL, palette, &paletteTexture);
	//Setup TEV (Texture Environment) Stage
	GX_SetTevOp(GX_TEVSTAGE0, GX_MODULATE);
	GX_SetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
	GX_SetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);

	f32 w = videoMode->viWidth;
	f32 h = videoMode->viHeight;

	//creates a perspective projection matrix with a view angle of 90,
	guPerspective(perspective, 45, (f32)w / h, 0.1F, 1000.0F);

	GX_LoadProjectionMtx(perspective, GX_PERSPECTIVE);
}

void GraphicsSystem::SetLight()
{
	guVector lpos;
	GXLightObj lobj;

	lpos.x = 0.0f;
	lpos.y = 100.0f;
	lpos.z = 0.0f;

	GX_InitLightPos(&lobj, lpos.x, lpos.y, lpos.z);
	GX_InitLightColor(&lobj, lightColor[0]);
	GX_LoadLightObj(&lobj, GX_LIGHT0);

	GX_SetNumChans(1);
	GX_SetChanCtrl(GX_COLOR0A0, GX_ENABLE, GX_SRC_REG, GX_SRC_VTX,
				   GX_LIGHT0, GX_DF_CLAMP, GX_AF_NONE);
	GX_SetChanAmbColor(GX_COLOR0A0, lightColor[1]);
}

bool GraphicsSystem::LoadMeshFromObj(string name, void *fileStream, unsigned int fileSize)
{

	//Temp variables to store obj
	vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	vector<guVector> temp_vertices;
	vector<guVector> temp_uvs;
	vector<guVector> temp_normals;

	FILE *file = fmemopen(fileStream, fileSize, "r");

	if (file == NULL)
		return false;

	while (1)
	{
		//its silly to assume the first world of a line wont be longer than 128
		char lineHeader[128];

		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

		// else : parse lineHeader

		if (strcmp(lineHeader, "v") == 0)
		{
			guVector vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0)
		{
			guVector uv;
			fscanf(file, "%f %f %f\n", &uv.x, &uv.y, &uv.z);
			temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0)
		{
			guVector normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0)
		{
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n",
								 &vertexIndex[0], &uvIndex[0], &normalIndex[0],
								 &vertexIndex[1], &uvIndex[1], &normalIndex[1],
								 &vertexIndex[2], &uvIndex[2], &normalIndex[2]);

			if (matches != 9)
			{
				printf("File can't be read by our simple parser : ( Try exporting with other options\n");
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
	}
	Mesh mesh;
	mesh.name = name;

	// For each vertex of each triangle
	for (unsigned int i = 0; i < vertexIndices.size(); i++)
	{
		unsigned int vertexIndex = vertexIndices[i];
		unsigned int uvIndex = uvIndices[i];
		unsigned int normalIndex = normalIndices[i];

		guVector vertex = temp_vertices[vertexIndex - 1];
		guVector uv = temp_uvs[uvIndex - 1];
		guVector normal = temp_normals[normalIndex - 1];

		mesh.vertices.push_back(vertex);
		mesh.uvs.push_back(uv);
		mesh.normals.push_back(normal);
	}

	meshCollection.push_back(mesh);

	return true;
}

void GraphicsSystem::DrawMeshes(vector<MeshComponent *> meshes, float deltaTime)
{
	//Load Texture into the hardware register
	GX_LoadTexObj(&paletteTexture, GX_TEXMAP0);

	GX_ClearVtxDesc();
	GX_SetVtxDesc(GX_VA_POS, GX_DIRECT);
	GX_SetVtxDesc(GX_VA_NRM, GX_DIRECT);
	GX_SetVtxDesc(GX_VA_TEX0, GX_DIRECT);

	for (u16 i = 0; i < meshes.size(); i++)
	{
		MeshComponent *currentMesh = meshes[i];
		TransformComponent meshObjectTransform = currentMesh->Owner->Transform;

		//unless you know what you're doing always Scale, Rotate then Translate
		guMtxIdentity(model);
		guMtxScaleApply(model, model, meshObjectTransform.Scale.x, meshObjectTransform.Scale.y, meshObjectTransform.Scale.z);

		Mtx tempRotMtx;
		c_guMtxQuat(tempRotMtx, &meshObjectTransform.Rotation);

		guMtxConcat(model, tempRotMtx, model);

		meshObjectTransform.Position.x -= 100 * deltaTime;

		guMtxTransApply(model, model, meshObjectTransform.Position.x, meshObjectTransform.Position.y, meshObjectTransform.Position.z);
		guMtxConcat(view, model, modelview);

		GX_LoadPosMtxImm(modelview, GX_PNMTX0);
		GX_LoadNrmMtxImm(modelview, GX_PNMTX0);

		GX_Begin(GX_TRIANGLES, GX_VTXFMT1, currentMesh->Vertices.size());
		for (unsigned int i = 0; i < currentMesh->Vertices.size(); i++)
		{
			guVector vertex = currentMesh->Vertices[i];
			guVector uvs = currentMesh->UVs[i];
			guVector normals = currentMesh->Normals[i];

			GX_Position3f32(vertex.x, vertex.y, vertex.z);
			GX_TexCoord2f32(uvs.x, uvs.y);
			GX_Normal3f32(normals.x, normals.y, normals.z);
		}
		GX_End();
	}
}

void GraphicsSystem::EndFrame()
{
	GX_SetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
	GX_SetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
	GX_SetAlphaUpdate(GX_TRUE);
	GX_SetColorUpdate(GX_TRUE);
	GX_CopyDisp(videoFrameBuffer[videoFrameBufferIndex], GX_TRUE);

	//Tells the graphics processor that we're done drawing for this frame and waits to be called again
	GX_DrawDone();

	//Cycle through the multibuffer
	VIDEO_SetNextFramebuffer(videoFrameBuffer[videoFrameBufferIndex]);

	VIDEO_Flush();
	VIDEO_WaitVSync();
	videoFrameBufferIndex ^= 1;
}