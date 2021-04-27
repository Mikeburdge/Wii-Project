#include "Systems\GraphicsSystem.h"

#include <string.h>

using namespace std;

GraphicsSystem::GraphicsSystem(){
	
	///Init vars
	camera = {0.0F, 0.0F, 0.0F};
	up = {0.0F, 1.0F, 0.0F};
	look = {0.0F, 0.0F, -1.0F};

	pitch = 0;
	yaw = 0;

	videoFrameBufferIndex = 0;

	background = {31, 179, 242, 0};

	//GX/VIDEO
	InitGXVideo();
}

GraphicsSystem* GraphicsSystem::myInstance = 0;

GraphicsSystem * GraphicsSystem::GetInstance()
{
	if (!myInstance)
	{
		myInstance = new GraphicsSystem();
	}
    return myInstance;
}

void GraphicsSystem::Init()
{    

}

void GraphicsSystem::Update(float deltaTime)
{

	// create a viewing matrix
	guLookAt(view, &camera, &up, &look);
	
	GX_Begin(GX_TRIANGLES,GX_VTXFMT0,3);

}

GraphicsSystem::~GraphicsSystem(){}

void GraphicsSystem::InitGXVideo(){
	
	VIDEO_Init();
	
	videoMode = VIDEO_GetPreferredMode(NULL);

	for(uint8_t videoIndex = 0; videoIndex < FRAMEBUFFER_SIZE; videoIndex++) {
		videoFrameBuffer[videoIndex] = (uint32_t *)MEM_K0_TO_K1(SYS_AllocateFramebuffer(videoMode));
		VIDEO_ClearFrameBuffer(videoMode, videoFrameBuffer[videoIndex], COLOR_BLACK);
	}
	videoFrameBufferIndex = 0;
	
	VIDEO_Configure(videoMode);
	VIDEO_SetNextFramebuffer(videoFrameBuffer[videoFrameBufferIndex]);
	VIDEO_SetBlack(FALSE);
	VIDEO_Flush();
	VIDEO_WaitVSync();
	
	if(videoMode->viTVMode & VI_NON_INTERLACE) {
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

	GX_SetViewport(0, 0,videoMode->fbWidth,videoMode->efbHeight, 0, 1);
	GX_SetScissor(0, 0, videoMode->fbWidth, videoMode->efbHeight);
	GX_SetDispCopySrc(0, 0, videoMode->fbWidth, videoMode->efbHeight);
	GX_SetDispCopyDst(videoMode->fbWidth, xfbHeight);
	GX_SetCopyFilter(videoMode->aa, videoMode->sample_pattern, GX_TRUE, videoMode->vfilter);

	// Store graphics system width and height
	gsWidth = (uint32_t)videoMode->fbWidth;
	gsHeight = (uint32_t)videoMode->efbHeight;
	
	GX_SetFieldMode(videoMode->field_rendering, ((videoMode->viHeight == 2 * videoMode->xfbHeight) ? GX_ENABLE : GX_DISABLE));

	// Anti-aliasing initialization
	if(videoMode->aa){
		GX_SetPixelFmt(GX_PF_RGB565_Z16, GX_ZC_LINEAR);
	}
	else{
		GX_SetPixelFmt(GX_PF_RGB8_Z24, GX_ZC_LINEAR);
	}

	GX_SetCullMode(GX_CULL_NONE);
	GX_CopyDisp(videoFrameBuffer[videoFrameBufferIndex], GX_TRUE);
	GX_SetDispCopyGamma(GX_GM_1_0);
	
	// set number of rasterized color channels
	GX_SetNumChans(1);

	//set number of textures to generate
	GX_SetNumTexGens(1);

	GX_InvVtxCache();
	GX_InvalidateTexAll();
	

	GX_SetVtxDesc(GX_VA_POS, GX_DIRECT);
	GX_SetVtxDesc(GX_VA_NRM, GX_DIRECT);
	GX_SetVtxDesc(GX_VA_TEX0, GX_DIRECT);

	GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
	GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_NRM_XYZ, GX_F32, 0);
	GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);


	// setup our projection matrix
	// this creates a perspective matrix with a view angle of 90,
	// and aspect ratio based on the display resolution
    f32 w = videoMode->viWidth;
    f32 h = videoMode->viHeight;	
	//Render mtx
	guPerspective(projection, 45, (f32)w/h, 0.1F, 1000.0F);
	GX_LoadProjectionMtx(projection, GX_PERSPECTIVE);
}