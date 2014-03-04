#ifndef GL_VFS_H
#define GL_VFS_H

#include "config.h"

namespace Gpu
{
    namespace OpenGL
    {
        class GlVideoDriverProxy;

        class PUNK_ENGINE_LOCAL VirtualFileSystem
        {
        public:
            VirtualFileSystem(GlVideoDriverProxy* impl);
            void RegisterNamedString(const char* name, const char* string);
            void RegisterNamedString(const char* name, const char* string, int size);
            bool IsRegisteredNamedString(const char* name) const;
        private:
            GlVideoDriverProxy* m_driver;
        };
    }
}
#endif // GL_VFS_H
