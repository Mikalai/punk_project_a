#include <graphics/opengl/module.h>
#include <system/filesystem/module.h>
#include <system/environment.h>
#include <string/module.h>
#include "gl_capabilities.h"
#include "gl_video_driver.h"
#include "gl_vfs.h"

#include <config.h>

PUNK_ENGINE_BEGIN
namespace Graphics {
    namespace OpenGL {

        void InitVfs(GlVideoDriver* impl)
        {
            auto vfs = impl->GetVirtualFileSystem();
            {
                System::Folder f;
                f.Open(System::Environment::Instance()->GetShaderFolder());
                Core::Buffer buffer;
                System::BinaryFile::Load("light.glsl", buffer); //  TODO: Do something better
                vfs->RegisterNamedString("/light.glsl", (char*)buffer.Data(), buffer.GetSize());
                System::BinaryFile::Load("material.glsl", buffer);
                vfs->RegisterNamedString("/material.glsl", (char*)buffer.Data(), buffer.GetSize());
            }
        }

        VirtualFileSystem::VirtualFileSystem(GlVideoDriver *impl)
            : m_driver(impl) {
            if (!IsShaderIncludeSupported(impl))
                throw Error::OpenGLException(L"GL_ARB_shading_language_include not supported");
        }

        void VirtualFileSystem::RegisterNamedString(const char *name, const char *string) {
            GL_CALL(glNamedStringARB(GL_SHADER_INCLUDE_ARB, -1, name, -1, string));
        }

        void VirtualFileSystem::RegisterNamedString(const char *name, const char *string, int size) {
            GL_CALL(glNamedStringARB(GL_SHADER_INCLUDE_ARB, -1, name, size, string));
        }

        bool VirtualFileSystem::IsRegisteredNamedString(const char *name) const {
            GL_CALL(bool res = glIsNamedStringARB(-1, name));
            return res;
        }
    }
}
PUNK_ENGINE_END
