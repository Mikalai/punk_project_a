#ifndef _H_PUNK_OPENGL_DRIVER
#define _H_PUNK_OPENGL_DRIVER

#include <vector>
#include <config.h>
#include <graphics/video_driver/module.h>
#include <graphics/video_driver/video_driver.h>
#include <graphics/render/irender.h>
#include "gl_settings.h"

PUNK_ENGINE_BEGIN
namespace Graphics
{
    class Texture2DArray;
    class Texture2D;
    class FrameBuffer;
    class VideoMemory;

    namespace OpenGL {

        class VideoMemory;
        class GlVideoDriverSettings;
        class VirtualFileSystem;
        class GlFrameBuffer;

        class PUNK_ENGINE_LOCAL GlVideoDriver : public VideoDriver {
        public:
            //	constructoion part
            GlVideoDriver();
            virtual ~GlVideoDriver();
			
			void QueryInterface(const Core::Guid& type, void** object) override;
			std::uint32_t AddRef() override;
			std::uint32_t Release() override;

			virtual void Initialize(ICanvas* canvas) override;
            ICanvas* GetCanvas() override;                        
            IVideoDriverSettings* GetSettings() override;
			ILowLevelRender* GetRender() override;

            VideoMemory* GetVideoMemory();
            const VideoMemory* GetVideoMemory() const;
            VirtualFileSystem* GetVirtualFileSystem();
            const VirtualFileSystem* GetVirtualFileSystem() const;
            bool IsFeatureSupported(const char* feature);

        private:

            int m_shader_version;
            int m_opengl_version;
            ICanvas* m_canvas {nullptr};
			OpenGL::VideoMemory* m_memory{ nullptr };
			VirtualFileSystem* m_vfs{ nullptr };
			GlVideoDriverSettings* m_caps{ nullptr };
			IRenderUniquePtr m_render{ nullptr, Core::DestroyObject };
			bool m_initialized{ false };
			std::atomic<std::uint32_t> m_ref_count{ 1 };

        private:
			void AssertInitialize() const;
            bool IsExtensionSupported(const char *extList, const char *extension);
            void Init();
            void Clear();
            void ReadConfig();
            void InitShaderPrograms();
            void SubscribeForSystemMessages();
            void InitInternalVertexBuffers();
        };
    }
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_OPENGL_DRIVER_LINUX
