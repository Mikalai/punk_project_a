#ifndef GL_FRAME_BUFFER_CONVERT_H
#define GL_FRAME_BUFFER_CONVERT_H

#include <graphics/opengl/module.h>

PUNK_ENGINE_BEGIN
namespace Graphics {
    enum class FrameBufferTarget;
    namespace OpenGL {
        GLenum Convert(const FrameBufferTarget& target);
    }
}
PUNK_ENGINE_END

#endif // GL_FRAME_BUFFER_CONVERT_H
