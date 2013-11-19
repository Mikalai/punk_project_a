#ifndef VIDEO_DRIVER_TYPE_H
#define VIDEO_DRIVER_TYPE_H

namespace Gpu
{
    enum class VideoDriverType {
        OPENGL,
        OPENGL_2_0,
        OPENGL_3_3,
        OPENGL_4_4,
        DIRECT3D_8,
        DIRECT3D_9C,
        DIRECT3D_10,
        DIRECT3D_11
    };
}

#endif // VIDEO_DRIVER_TYPE_H
