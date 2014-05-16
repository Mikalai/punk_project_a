#include <vector>
#include <memory.h>
#include <images/module.h>
#include <graphics/error/module.h>
#include <graphics/frame_buffer/module.h>
#include <graphics/texture/module.h>
#include <graphics/canvas/module.h>
#include <system/window/iwindow.h>
#include "ivideo_driver_settings.h"
#include "video_driver.h"

PUNK_ENGINE_BEGIN
namespace Graphics
{
//    Frame* VideoDriver::BeginFrame()
//    {
//        //  TODO: Safer resource managment should be made here
//        //Frame* frame = new Frame(this);
//        return nullptr;//frame;
//    }
//
//    void VideoDriver::EndFrame(Frame* value)
//    {
//        //  TODO: Safer resource managment should be made here
////        delete value;
////        SwapBuffers();
//    }

    VideoDriver::~VideoDriver()
    {}    
}
PUNK_ENGINE_END
