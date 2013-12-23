
#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif // NOMINMAX
#include <Windows.h>
#elif defined __gnu_linux__
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#endif

#include <string/module.h>
#include <system/errors/module.h>
#include "folder.h"

PUNK_ENGINE_BEGIN
namespace System
{
    Folder::Folder() {}

    Folder::~Folder() {
        Close();
    }

    bool Folder::Open(const Core::String& name) {
#ifdef _WIN32
        m_prev_folder_name = GetCurrentFolder();
        if (SetCurrentDirectoryW((LPCWSTR)name.ToWchar().Data()) == TRUE) {
            return true;
        }

        //	try to create
        if (CreateDirectoryW((LPCWSTR)name.ToWchar().Data(), 0) != 0) {
            if (SetCurrentDirectoryW((LPCWSTR)name.ToWchar().Data()) == TRUE) {
                return true;
            }
        }
        return false;
#elif defined __gnu_linux__
        m_prev_folder_name = GetCurrentFolder();

        if (!chdir(&name.ToUtf8()[0]))
            return true;

        if (mkdir(&name.ToUtf8()[0], 0))
            if (!chdir(&name.ToUtf8()[0]))
                return true;
        return false;
#endif
    }

    bool Folder::IsContain(const Core::String& name) const
    {

#ifdef _WIN32
        WIN32_FIND_DATA dir;
        HANDLE file;

        wchar_t dirName[256];
        GetCurrentDirectory(256, dirName);
        file = FindFirstFile(dirName, &dir);

        do
        {
            if (name == dir.cFileName)
                return true;
        }
        while (FindNextFile(file, &dir));
        return false;
#elif defined __gnu_linux__
        struct dirent *de = NULL;
        DIR *d = NULL;
        char* folder = getcwd(0, 0);
        d = opendir(folder);
        free(folder);
        if(d == NULL)
        {
            return false;
        }

        // Loop while not NULL
        while (de = readdir(d))
        {
            Core::String file = Core::String::FromUtf8(de->d_name);
            if (file == name)
            {
                closedir(d);
                return true;
            }
        }

        closedir(d);
        return false;
#endif
    }

    void Folder::Close()
    {
#ifdef _WIN32
        SetCurrentDirectoryW((LPCWSTR)m_prev_folder_name.ToWchar().Data());
#elif defined __gnu_linux__
        auto buffer = m_prev_folder_name.ToUtf8();
        if (chdir(&buffer[0]))
            throw System::PunkException(L"Can't close folder" + m_folder_name);
#endif
    }

    const Core::StringList Folder::ListAllItems()
    {
        Core::StringList res;

#ifdef _WIN32
        WIN32_FIND_DATA dir;
        wchar_t dirName[256];
        GetCurrentDirectoryW(256, dirName);
        HANDLE file = FindFirstFileW(L"*", &dir);

        if (file != INVALID_HANDLE_VALUE)
        {
            do
            {
                Core::String f = Core::String(dir.cFileName);
                if (f == L"." || f == L"..")	//skip this and parent
                    continue;
                res.Push(f);
            }
            while (FindNextFileW(file, &dir));
        }
#endif	//	_WIN32

        return res;
    }

    const Core::String& Folder::Name() const
    {
        return m_folder_name;
    }

    void Folder::DeleteFile(const Core::String& path)
    {
#ifdef _WIN32
        ::DeleteFileW((LPCWSTR)path.ToWchar().Data());
#elif defined __gnu_linux__
        unlink(&path.ToUtf8()[0]);
#endif

    }

    const Core::StringList Folder::Find(const Core::String& name) const
    {
        Core::StringList res;

#ifdef _WIN32
        WIN32_FIND_DATA dir;
        wchar_t dirName[256];
        GetCurrentDirectoryW(256, dirName);
        HANDLE file = FindFirstFileW((LPCWSTR)name.ToWchar().Data(), &dir);

        if (file != INVALID_HANDLE_VALUE)
        {
            do
            {
                Core::String f = Core::String(dir.cFileName);
                if (f == L"." || f == L"..")	//skip this and parent
                    continue;
                //if (wcswcs(dir.cFileName, name.Data()))
                res.Push(f);
            }
            while (FindNextFileW(file, &dir));
        }
#endif	//	_WIN32

        return res;
    }

    const Core::String Folder::GetCurrentFolder()
    {
#ifdef _WIN32
        wchar_t buf[MAX_PATH];
        GetCurrentDirectoryW(MAX_PATH, buf);
        return Core::String(buf);
#elif defined __gnu_linux__
        char* res = getcwd(nullptr, 0);
        try
        {
            Core::String str(res);
            free(res);
            return str;
        }
        catch(...)
        {
            free(res);
            throw;
        }
#endif
    }

    void Folder::SetCurrentFolder(const Core::String& value)
    {
#ifdef _WIN32
        SetCurrentDirectoryW((LPCWSTR)value.ToWchar().Data());
#elif defined __gnu_linux__
        chdir(&value.ToUtf8()[0]);
#endif
    }
}
PUNK_ENGINE_END
