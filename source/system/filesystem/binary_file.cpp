#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif	//	NOMINMAX
#include <Windows.h>
#elif defined __linux__
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#endif

#include <iostream>
#include <istream>
#include <string/string.h>
#include <string/buffer.h>
#include <system/errors/module.h>
#include "binary_file.h"

PUNK_ENGINE_BEGIN
namespace System
{
#ifdef _WIN32
    size_t GetFileSize(std::intptr_t hFile)
    {
        DWORD high;
        DWORD low = ::GetFileSize((HANDLE)hFile, &high);
#ifdef _WIN64
        size_t result = (size_t)high << 32 || low;
        return result;
#elif defined _WIN32
        return low;
#endif  //  _WIN64
    }

    std::intptr_t OpenReadFile(const Core::String& filename)
    {
        HANDLE hFile = CreateFileW((LPWSTR)filename.ToWchar().Data(), GENERIC_READ, FILE_SHARE_READ|FILE_SHARE_WRITE, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        CHECK_SYS_ERROR(L"Error in binary file, can't load it " + filename);
        return (std::intptr_t)hFile;
    }

    void CloseFile(std::intptr_t hFile)
    {
        CloseHandle((HANDLE)hFile);
        CHECK_SYS_ERROR(Core::String("Binary file close failed"));
    }

    void ReadFile(std::intptr_t hFile, void* ptr, size_t size)
    {
        DWORD read;
        ::ReadFile((HANDLE)hFile, ptr, size, &read, 0);
        CHECK_SYS_ERROR(Core::String("Error in binary file, can't read data"));

        if (read != (DWORD)size)
            throw Error::OSException("Error in binary file, read data less than file contains, possible bad staff happenes");
    }

#elif defined __linux__
    size_t GetFileSize(int hFile)
    {
        __off_t size = lseek(hFile, 0, SEEK_END);
        lseek(hFile, 0, SEEK_SET);
        return (size_t)size;
    }

    int OpenReadFile(const Core::String& filename)
    {
        auto buffer = filename.ToUtf8();
        buffer.push_back(0);
        int hFile = open(&buffer[0], O_RDONLY);
        return hFile;
    }

    void CloseFile(int handle)
    {
        close(handle);
    }

    void ReadFile(int handle, void* ptr, size_t size)
    {
        size_t res = read(handle, ptr, size);
       // std::cout << "Read result: " << res << std::endl;
    }

#endif

    bool BinaryFile::Load(std::istream& stream, Core::Buffer& buffer)
	{
		stream.seekg(0, std::ios_base::end);
		std::streamoff size = stream.tellg();
		stream.seekg(0, std::ios_base::beg);
		buffer.SetSize((int)size);
        stream.read(reinterpret_cast<char*>(buffer.Data()), size);
		return true;
	}

    bool BinaryFile::Load(const Core::String& filename, Core::Buffer& buffer)
	{
        std::intptr_t hFile = (std::intptr_t)OpenReadFile(filename);
        if (hFile == (std::intptr_t)-1)
            return false;
        size_t size = GetFileSize(hFile);
        if (size == 0)
        {
            CloseFile(hFile);
            return false;
        }
        buffer.SetSize(size);
        ReadFile(hFile, buffer.Data(), size);
        CloseFile(hFile);
		return true;
	}

    bool BinaryFile::Save(const Core::String& filename, const Core::Buffer& buffer)
	{
#ifdef _WIN32

        HANDLE hFile = CreateFileW((LPCWSTR)filename.ToWchar().Data(), GENERIC_WRITE, 0, 0,CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		CHECK_SYS_ERROR(L"Error in binary file, open file for saving " + filename);

        DWORD written;
        WriteFile(hFile, (LPCVOID)buffer.Data(), (DWORD)buffer.GetSize(), &written, 0);
		CHECK_SYS_ERROR(L"Error in binary file, can't write data to file " + filename);

        if (written != (DWORD)buffer.GetSize())
            throw Error::OSException(L"Error in binary file, written data is less than should be " + filename);

		CloseHandle(hFile);
		CHECK_SYS_ERROR(L"Saving binary file failed " + filename);
#endif	//	_WIN32
		return true;
	}

    bool BinaryFile::Append(const Core::String& filename, const Core::Buffer& buffer)
	{
#ifdef _WIN32
        HANDLE hFile = CreateFileW((LPCWSTR)filename.ToWchar().Data(), GENERIC_WRITE, 0, 0, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		CHECK_SYS_ERROR(L"Error in binary file, can't open file for appending it " + filename);

        DWORD offset = GetFileSize((std::intptr_t)hFile);
		SetFilePointer(hFile, offset, 0, FILE_BEGIN);

        DWORD written;
        WriteFile(hFile, (LPCVOID)buffer.Data(), (DWORD)buffer.GetSize(), &written, 0);
		CHECK_SYS_ERROR(L"Error in binary file, can't write data to file " + filename);

        if (written != static_cast<DWORD>(buffer.GetSize()))
            throw Error::OSException(L"Error in binary file, written data is less than should be in " + filename);

		CloseHandle(hFile);
		CHECK_SYS_ERROR(L"Failed to append a file " + filename);
#endif	//	_WIN32
		return true;
	}

    bool BinaryFile::Truncate(const Core::String& filename)
	{
#ifdef _WIN32
		DWORD error = GetLastError();

        HANDLE hFile = CreateFileW((LPCWSTR)filename.ToWchar().Data(), GENERIC_WRITE, 0, 0, TRUNCATE_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		error = GetLastError();
		if (error == ERROR_FILE_NOT_FOUND || error == ERROR_SUCCESS)
			return true;				
		SetLastError(error);
		CHECK_SYS_ERROR(L"Error can't truncate binary file " + filename);

		CloseHandle(hFile);
		CHECK_SYS_ERROR(L"Failed to truncate a file " + filename);
#endif	//	_WIN32
		return true;
	}
}
PUNK_ENGINE_END
