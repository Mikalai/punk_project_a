#include "opengl/common/gl_proxy_video_driver.h"
#include "opengl/common/gl_capabilities.h"
#include "opengl/common/extensions.h"
#include "opengl/common/error/module.h"
#include "gl_vfs.h"

namespace Gpu
{
    namespace OpenGL
    {
        VirtualFileSystem::VirtualFileSystem(GlVideoDriverProxy *impl)
            : m_driver(impl)
        {
            if (!IsShaderIncludeSupported(impl))
                throw System::PunkException(L"GL_ARB_shading_language_include not supported");
        }

        void VirtualFileSystem::RegisterNamedString(const char *name, const char *string)
        {
            GL_CALL(glNamedStringARB(GL_SHADER_INCLUDE_ARB, -1, name, -1, string));
        }

        void VirtualFileSystem::RegisterNamedString(const char *name, const char *string, int size)
        {
            GL_CALL(glNamedStringARB(GL_SHADER_INCLUDE_ARB, -1, name, size, string));
        }

        bool VirtualFileSystem::IsRegisteredNamedString(const char *name) const
        {
            GL_CALL(bool res = glIsNamedStringARB(-1, name));
            return res;
        }
    }
}
