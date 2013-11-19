#ifndef VIDEO_DRIVER_CREATOR_H
#define VIDEO_DRIVER_CREATOR_H

#include "../../config.h"
#include "video_driver_type.h"

namespace Gpu
{
    class VideoDriver;
    PUNK_ENGINE_API VideoDriver* CreateVideoDriver(const VideoDriverType& type);
}

#endif // VIDEO_DRIVER_CREATOR_H
