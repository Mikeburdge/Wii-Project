#include "Systems/GraphicsSystem.h"

//fmemopen
#include <stdio.h>


#include <vector>
#include <string.h>
#include "ogc/gu.h"

using namespace std;

GraphicsSystem::GraphicsSystem()
{
	pitch = 0;
	yaw = 0;

	videoFrameBufferIndex = 0;

	lightColor[0] = {255, 255, 255, 255};
	lightColor[1] = {150, 150, 150, 255};

	background = {80, 80, 255, 0};

	//Initialises the video
	InitGXVideo();

	// Initialize the camera.
	CameraInit();
}

GraphicsSystem::~GraphicsSystem() {}

GraphicsSystem *GraphicsSystem::myInstance = 0;

GraphicsSystem *GraphicsSystem::GetInstance()
{
	if (!myInstance)
	{
		myInstance = new GraphicsSystem();
	}
	return myInstance;
}

void GraphicsSystem::Init() {}

void GraphicsSystem::Update(float deltaTime)
{

	//Create a viewing matrix
	guLookAt(view, &camPt, &up, &origin);

	//Update Lighting
	SetLight();

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

	// set number of rasterized color channels
	GX_SetNumChans(1);

	//set number of textures to generate
	GX_SetNumTexGens(1);

	//Invalidates the vertex cache and current texture memory cache
	GX_InvVtxCache();
	GX_InvalidateTexAll();
}

void GraphicsSystem::CameraInit(void)
{
	camPt = {0.0F, 0.0F, 0.0F};
	up = {0.0F, 1.0F, 0.0F};
	origin = {0.0F, 0.0F, -1.0F};

	f32 w = videoMode->viWidth;
	f32 h = videoMode->viHeight;

	//creates a perspective projection matrix with a view angle of 90,
	guPerspective(projection, 45, (f32)w / h, 0.1F, 1000.0F);

	GX_LoadProjectionMtx(projection, GX_PERSPECTIVE);
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

bool LoadMeshFromObj(string name, void *fileStream, unsigned int fileSize)
{

	//Temp variables to store obj
	vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	vector<guVector> vertices;
	vector<guVector> uvs;
	vector<guVector> normals;

	FILE *file = fmemopen(fileStream, fileSize, "r");
	if (file == NULL)
	{
		printf("Impossible to open the file !\n");
		return false;
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