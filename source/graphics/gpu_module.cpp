#include "module.h"
#include "opengl/module.h"

namespace Gpu
{
    VideoDriver* Init(const VideoDriverDesc& data)
	{
        OpenGL::GlVideoDriver_3_3* driver = new OpenGL::GlVideoDriver_3_3(data);
        OpenGL::InitOpenGL(driver);
        return driver;
	}

    void Destroy(VideoDriver *driver)
	{		
		Frame::ClearPool();
		TextureContext::ClearPool();
		CoreState::ClearPool();
        OpenGL::DestroyOpenGL();
        delete driver;
	}
}
