#ifdef WIN32
#include <windows.h>
#endif

#include <stdexcept>
#include <string/module.h>
#include <system/errors/module.h>
#include "mapped_buffer.h"

PUNK_ENGINE_BEGIN
namespace System {

    namespace __private {

    PUNK_ENGINE_LOCAL std::uint32_t GetPageSize() {
#ifdef _WIN32
        SYSTEM_INFO info;
        GetSystemInfo(&info);
        return info.dwPageSize;
#elif defined __linux__
        return 0;
#endif
    }

    struct PUNK_ENGINE_LOCAL MappedBufferImpl {
#ifdef _WIN32
        DWORD m_window_size;
        HANDLE m_file;
        HANDLE m_map;
        DWORD m_page_size;
        void* m_data;
        DWORD m_current_window;
        DWORD m_file_size;
#elif defined __linux__
#endif

#ifdef WIN32
        MappedBufferImpl(const Core::String& filename, std::uint32_t wnd_size)
            : m_window_size(wnd_size)
            , m_page_size(GetPageSize())
            , m_data(0)
            , m_current_window(0)
            , m_file_size(0)
        {
            m_file = CreateFileW((LPCWSTR)filename.ToWchar().Data(), GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
            if (m_file == INVALID_HANDLE_VALUE)
                throw Error::OSException(L"Failed to open file " + filename);

            m_file_size = GetFileSize(m_file, 0);
            if (m_file_size == INVALID_FILE_SIZE) {
                CloseHandle(m_file);
                throw Error::OSException(L"Failed to get file size of " + filename);
            }

            m_map = CreateFileMappingA(m_file, 0, PAGE_READONLY, 0, 0, 0);
            if (!m_map) {
                CloseHandle(m_file);
                throw Error::OSException(L"Failed to map file " + filename);
            }
        }
#elif defined __linux__
        MappedBufferImpl(const Core::String& filename, std::uint32_t wnd_size)
        {
            (void)filename;
            (void)wnd_size;
        }
#endif

        ~MappedBufferImpl() {
#ifdef WIN32
            if (m_data) {
                UnmapViewOfFile(m_data);
                m_data = 0;
            }

            if (m_map) {
                CloseHandle(m_map);
                m_map = 0;
            }

            if (m_file) {
                CloseHandle(m_file);
                m_file = 0;
            }
#elif defined __linux__
#endif
        }

        void* Get(std::uint32_t offset) {
#ifdef WIN32
            if (offset >= m_file_size)
                return 0;
            DWORD required_window = offset / (m_page_size * m_window_size);
            DWORD window_offset = offset % (m_page_size * m_window_size);
            if (required_window != m_current_window)
            {
                if (m_data)
                {
                    UnmapViewOfFile(m_data);
                    m_data = 0;
                }
                m_current_window = required_window;
            }

            if (!m_data)
            {
                DWORD expected_size = (m_current_window + 1) * m_window_size * m_page_size;
                DWORD bytes_to_read = (m_file_size < expected_size ? m_file_size - m_current_window * m_window_size * m_page_size : m_window_size * m_page_size);
                m_data = MapViewOfFile(m_map, FILE_MAP_READ, 0, m_current_window * m_window_size * m_page_size, bytes_to_read);
                if (!m_data)
                {
                    DWORD error = GetLastError();
                    if (error == ERROR_NOT_ENOUGH_MEMORY)
                    {
                        throw std::bad_alloc();
                    }
                    else
                    {
                        throw std::runtime_error("Can't map view of file");
                    }
                }
            }
            void* ptr = (void*)((char*)m_data + window_offset);
            return ptr;
#elif defined __linux__
            (void)offset;
            return nullptr;
#endif
        }
    };
    }

    MappedBuffer::MappedBuffer(const Core::String& filename, std::uint32_t wnd_size)
        : impl{new __private::MappedBufferImpl{filename, wnd_size}} {}

    MappedBuffer::~MappedBuffer() {
        delete impl;
        impl = nullptr;
    }

    void* MappedBuffer::Get(std::uint32_t offset) {
        return impl->Get(offset);
    }

}
PUNK_ENGINE_END

/** \} */
