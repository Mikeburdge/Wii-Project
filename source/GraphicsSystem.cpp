#include "Systems\GraphicsSystem.h"

#include <string.h>

using namespace std;

GraphicsSystem::GraphicsSystem(){
	
	///Init vars
	m_cam = {0.0F, 0.0F, 0.0F};
	m_up = {0.0F, 1.0F, 0.0F};
	m_look = {0.0F, 0.0F, -1.0F};

	m_pitch = 0;
	m_yaw = 0;

	videoFrameBufferIndex = 0;

	//GX/VIDEO
	InitGXVideo();
}

GraphicsSystem* GraphicsSystem::m_instance = 0;

GraphicsSystem * GraphicsSystem::GetInstance()
{
	if (!m_instance)
	{
		m_instance = new GraphicsSystem();
	}
    return m_instance;
}



void GraphicsSystem::Init()
{    

}

void GraphicsSystem::Update(float deltaTime)
{

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
	GX_SetCopyClear(m_background, 0x00ffffff);

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
	
	// Texture vertex format setup
	GX_ClearVtxDesc();


	// set number of rasterized color channels
	GX_SetNumChans(1);

	//set number of textures to generate
	GX_SetNumTexGens(1);

	GX_InvVtxCache();
	GX_InvalidateTexAll();
	
	// //Loads palette.bmp texture unused right now will look into later when i can render anything
	// TPL_OpenTPLFromMemory(&m_paletteTPL, (void *)palette_tpl,palette_tpl_size);
	// TPL_GetTexture(&m_paletteTPL,palette,&m_paletteTexture);
	
	// //Setup TEV (Texture Environment) Stage
	// GX_SetTevOp(GX_TEVSTAGE0, GX_MODULATE);
	// GX_SetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
	// GX_SetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);	

	// setup our projection matrix
	// this creates a perspective matrix with a view angle of 90,
	// and aspect ratio based on the display resolution
    f32 w = videoMode->viWidth;
    f32 h = videoMode->viHeight;	
	//Render mtx
	guPerspective(m_projection, 45, (f32)w/h, 0.1F, 1000.0F);
	GX_LoadProjectionMtx(m_projection, GX_PERSPECTIVE);
}