#include <string.h>
#include <string/module.h>
#include <system/concurrency/module.h>
#include <system/logger/module.h>
#include <graphics/opengl/module.h>
#include "video_memory.h"
#include "nvx_gpu_memory_info.h"
#include "ati_meminfo.h"

PUNK_ENGINE_BEGIN
using namespace Core;
namespace Graphics {
    namespace OpenGL {

        System::ThreadMutex g_memory_mutex;
        VideoMemory* g_memory;

        VideoMemory::VideoMemory() {
            m_logger = System::GetDefaultLogger();
            memset(&m_core, 0, sizeof(m_core));
			GLint mem[5] = {0, 0, 0, 0};
            GL_CALL(glGetIntegerv(GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX, &mem[0]));
			m_core.m_max_mem_available = mem[0] * 1024;	//	convert from kb to b
            GL_CALL(glGetIntegerv(GPU_MEMORY_INFO_DEDICATED_VIDMEM_NVX, &mem[1]));
            GL_CALL(glGetIntegerv(GPU_MEMORY_INFO_TOTAL_AVAILABLE_MEMORY_NVX, &mem[2]));
            GL_CALL(glGetIntegerv(GPU_MEMORY_INFO_EVICTION_COUNT_NVX, &mem[3]));
            GL_CALL(glGetIntegerv(GPU_MEMORY_INFO_EVICTED_MEMORY_NVX, &mem[4]));
			m_core.m_max_mem_usage = (m_core.m_max_mem_available << 1) / 3;
		}

        VideoMemory::~VideoMemory() {
            m_logger->Info(String(L"{0} pixel buffers left").arg(m_pbo_list.size()));
			while (!m_pbo_list.empty())
			{
				delete m_pbo_list.back();
				m_pbo_list.pop_back();
			}

            m_logger->Info(String(L"{0} vertex buffers left").arg(m_vbo_list.size()));
			while (!m_vbo_list.empty())
			{
				delete m_vbo_list.back();
				m_vbo_list.pop_back();
			}

            m_logger->Info(String(L"{0} index buffers left").arg(m_ibo_list.size()));
			while (!m_ibo_list.empty())
			{
				delete m_ibo_list.back();
				m_ibo_list.pop_back();
			}
		}

        void VideoMemory::SetMaxMemoryUsage(std::uint32_t value)
		{
            (void)value;
            throw Error::GraphicsException(L"VideoMemory::SetMaxMemoryUsage not implemented");
		}

        std::uint32_t VideoMemory::GetMaxMemoryUsage() const
		{
			return m_core.m_max_mem_usage;
		}

        std::uint32_t VideoMemory::GetMemoryUsage() const
		{
			return m_core.m_mem_usage;
		}

        std::uint32_t VideoMemory::GetMaxAvailableMemory() const
		{
			return m_core.m_max_mem_available;
		}

        PixelBufferObject* VideoMemory::AllocatePixelBuffer(std::uint32_t size)
		{
			VerifyMemory(size);
			PixelBufferObject* value(new PixelBufferObject);
			try
			{
				value->Create(0, size);
				m_core.m_mem_usage += size;
				return value;
			}
			catch(...)
			{
				delete value;
                throw Error::GraphicsException(L"Failed to allocate memory for pixel buffer");
			}
		}

        void VideoMemory::FreePixelBuffer(IBufferObject* v)
		{
            PixelBufferObject* value = dynamic_cast<PixelBufferObject*>(v);
			if (!value)
				return;
            std::uint32_t size = value->GetSize();
			delete value;
			m_core.m_mem_usage -= size;
		}

        VertexBufferObject* VideoMemory::AllocateVertexBuffer(std::uint32_t size)
		{
			VerifyMemory(size);
			VertexBufferObject* value(new VertexBufferObject);
			try
			{
				value->Create(0, size);
				m_core.m_mem_usage += size;
				return value;
			}
			catch(...)
			{
				delete value;
                throw Error::GraphicsException(L"Failed to allocate memory for vertex buffer");
			}
		}

        void VideoMemory::FreeVertexBuffer(IBufferObject* v)
		{
            VertexBufferObject* value = dynamic_cast<VertexBufferObject*>(v);
			if (!value)
				return;
            std::uint32_t size = value->GetSize();
			delete value;
			m_core.m_mem_usage -= size;
		}

        IndexBufferObject* VideoMemory::AllocateIndexBuffer(std::uint32_t size)
		{
			VerifyMemory(size);
			IndexBufferObject* value(new IndexBufferObject);
			try
			{
				value->Create(0, size);
				m_core.m_mem_usage += size;
				return value;
			}
			catch(...)
			{
				delete value;
                throw Error::GraphicsException(L"Failed to allocate memory for index buffer");
			}
		}

        void VideoMemory::FreeIndexBuffer(IBufferObject* v)
		{
            IndexBufferObject* value = dynamic_cast<IndexBufferObject*>(v);
			if (!value)
				return;
            std::uint32_t size = value->GetSize();
			delete value;
			m_core.m_mem_usage -= size;
		}

        bool VideoMemory::VerifyMemory(std::uint32_t size)
		{
			if (m_core.m_mem_usage + size >= m_core.m_max_mem_usage)
				throw OpenGLOutOfMemoryException(L"Not enough video memory to allocate buffer");
			return true;
		}

        //void VideoMemory::OptimizeMemoryUsage(std::uint32_t size)
		//{
        //	std::uint32_t to_free override;
		//	//	remove useless textures
        //	for (std::uint32_t i = 0; i < m_pbo_list.size(); ++i)
		//	{
		//		if (m_pbo_list[i].GetCount() == 1)
		//			to_free += m_pbo_list[i]->GetSize();
		//		if (m_core.m_mem_usage - to_free + size < m_core.m_max_mem_usage)
		//			return;
		//	}

		//	//	remove useless vbo
        //	for (std::uint32_t i = 0; i < m_vbo_list.size(); ++i)
		//	{
		//		if (m_vbo_list[i].GetCount() == 1)
		//			to_free += m_vbo_list[i]->GetSize();
		//		if (m_core.m_mem_usage - to_free + size < m_core.m_max_mem_usage)
		//			return;
		//	}

		//	//	remove useless ibo
        //	for (std::uint32_t i = 0; i < m_ibo_list.size(); ++i)
		//	{
		//		if (m_ibo_list[i].GetCount() == 1)
		//			to_free += m_ibo_list[i]->GetSize();
		//		if (m_core.m_mem_usage - to_free + size < m_core.m_max_mem_usage)
		//			return;
		//	}
		//}        
	}

    namespace Constructor {
        extern "C" PUNK_ENGINE_API IVideoMemory* GetVideoMemory() {
            System::ThreadMutexLock lock(OpenGL::g_memory_mutex);
            if (!OpenGL::g_memory)
                OpenGL::g_memory = new OpenGL::VideoMemory();
            return OpenGL::g_memory;
        }

        extern "C" PUNK_ENGINE_API void DestroyVideoMemory() {
            System::ThreadMutexLock lock(OpenGL::g_memory_mutex);
            delete OpenGL::g_memory;
            OpenGL::g_memory = nullptr;
        }
    }
}
PUNK_ENGINE_END
