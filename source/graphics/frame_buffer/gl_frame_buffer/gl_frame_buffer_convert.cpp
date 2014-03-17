#include "gl_frame_buffer_convert.h"
#include <graphics/frame_buffer/frame_buffer_target.h>
#include <graphics/error/module.h>

PUNK_ENGINE_BEGIN
namespace Graphics {
    namespace OpenGL {

        GLenum Convert(const FrameBufferTarget& target) {
            switch(target) {
            case FrameBufferTarget::TargetBack:
                return GL_BACK;
            case FrameBufferTarget::TargetBackLeft:
                return GL_BACK_LEFT;
            case FrameBufferTarget::TargetBackRight:
                return GL_BACK_RIGHT;
            case FrameBufferTarget::TargetFront:
                return GL_FRONT;
            case FrameBufferTarget::TargetFrontBack:
                return GL_FRONT_AND_BACK;
            case FrameBufferTarget::TargetFrontLeft:
                return GL_FRONT_LEFT;
            case FrameBufferTarget::TargetFrontRight:
                return GL_FRONT_RIGHT;
            case FrameBufferTarget::TargetLeft:
                return GL_LEFT;
            case FrameBufferTarget::TargetNone:
                return GL_NONE;
            case FrameBufferTarget::TargetRight:
                return GL_RIGHT;
            }
            throw Error::InvalidFrameBufferTarget(L"Can't convert frame buffer target");
        }
    }
}
PUNK_ENGINE_END
