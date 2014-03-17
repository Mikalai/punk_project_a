#ifndef GL_VFS_H
#define GL_VFS_H

#include <config.h>

PUNK_ENGINE_BEGIN
namespace Graphics {
    namespace OpenGL {

        class GlVideoDriver;

        class PUNK_ENGINE_LOCAL VirtualFileSystem
        {
        public:
            VirtualFileSystem(GlVideoDriver* impl);
            void RegisterNamedString(const char* name, const char* string);
            void RegisterNamedString(const char* name, const char* string, int size);
            bool IsRegisteredNamedString(const char* name) const;
        private:
            GlVideoDriver* m_driver;
        };
    }
}
PUNK_ENGINE_END

#endif // GL_VFS_H
