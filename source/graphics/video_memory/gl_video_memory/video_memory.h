#ifndef _H_PUNK_OPENGL_VIDEO_MEMORY
#define _H_PUNK_OPENGL_VIDEO_MEMORY

#include <memory>
#include <vector>
#include <config.h>
#include <cstdint>
#include <graphics/video_memory/ivideo_memory.h>
#include <graphics/buffers/pbo.h>
#include <graphics/buffers/vbo.h>
#include <graphics/buffers/ibo.h>

PUNK_ENGINE_BEGIN
namespace System { class ILogger; }
namespace Graphics {
		
	namespace OpenGL {		

		/**
		*	This class is responsible for video memory usage
		*	Only this class can allocate video memory for
		*	textures and buffers.
		*	This is a singletone class
		*/
        class PUNK_ENGINE_LOCAL VideoMemory : public IVideoMemory {
		public:

			VideoMemory();
            virtual~VideoMemory();

            void SetMaxMemoryUsage(std::uint32_t value) override;
            std::uint32_t GetMaxMemoryUsage() const override;
            std::uint32_t GetMemoryUsage() const override;
            std::uint32_t GetMaxAvailableMemory() const override;
   //         IBufferObject* AllocatePixelBuffer(std::uint32_t size) override;
   //         void FreePixelBuffer(IBufferObject* value) override;
			//IBufferObject* AllocateVertexBuffer(std::uint32_t size) override;
   //         void FreeVertexBuffer(IBufferObject* value) override;
			//IBufferObject* AllocateIndexBuffer(std::uint32_t size) override;
   //         void FreeIndexBuffer(IBufferObject* value) override;

		private:

            bool VerifyMemory(std::uint32_t size);

			/**
			*	This will use async procedures to find all invalid objects and
			*	when list of old objects will be created in the main stream
			*	memory freeing should be performed
			*/
			void OptimizeMemoryUsage(size_t size);

        //	static std::unique_ptr<VideoMemory> m_instance;

			struct Core
			{
				size_t m_max_mem_usage;
				size_t m_mem_usage;
				size_t m_max_mem_available;
			};

			Core m_core;

            /*std::vector<PixelBufferObject*> m_pbo_list;
			std::vector<VertexBufferObject*> m_vbo_list;
			std::vector<IndexBufferObject*> m_ibo_list;*/
            System::ILogger* m_logger {nullptr};
		};
	}
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_OPENGL_VIDEO_MEMORY
