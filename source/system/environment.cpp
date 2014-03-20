#include <string/string.h>
#include <system/filesystem/module.h>
#include "environment.h"

PUNK_ENGINE_BEGIN
namespace System
{
	Environment* Environment::m_instance;

	Environment* Environment::Instance()
	{
		if (!m_instance)
			m_instance = new Environment;
		return m_instance;
	}

	void Environment::Destroy()
	{
		delete m_instance;
        m_instance = 0;
	}
	
	Environment::Environment()
	{
		//System::ConfigFile file;
		//file.Open(System::Window::Instance()->GetTitle());
		//	file.WriteOptionString(L"data", L"d:\\project\\data\\");	
		//if (!file.IsExistOption(L"data"))
		//	
		//file.Close();
	}

    const Core::String Environment::GetCurrentFolder()
	{
		return Folder::GetCurrentFolder();
	}

    void Environment::SetCurrentFolder(const Core::String& dir)
	{
		Folder::SetCurrentFolder(dir);
	}

    const Core::String Environment::GetFontFolder()
	{
        return GetCurrentFolder() + L"/../../data/fonts/";
		//return GetCurrentFolder() + L"fonts\\";
	}

    const Core::String Environment::GetModelFolder()
	{
        return GetCurrentFolder() + L"/../../data/models/";
		//return GetCurrentFolder() + L"models\\";
	}

    const Core::String Environment::GetMapFolder()
	{
		return GetCurrentFolder() + L"\\..\\..\\data\\maps\\";
		//return GetCurrentFolder() + L"maps\\";
	}

    const Core::String Environment::GetSaveFolder()
	{
		return GetCurrentFolder() + L"\\..\\..\\data\\saves\\";
		//return GetCurrentFolder() + L"saves\\";
	}

    const Core::String Environment::GetTextureFolder()
	{
#ifdef _WIN32
        return GetCurrentFolder() + L"\\..\\..\\data\\textures\\";
        //return GetCurrentFolder() + L"textures\\";
#elif defined __gnu_linux__
        return GetCurrentFolder() + L"/../../data/textures/";
#endif
	}

    const Core::String Environment::GetQuestFolder()
	{
		return GetCurrentFolder() + L"\\..\\..\\data\\quests\\";
		//return GetCurrentFolder() + L"quests\\";
	}

    const Core::String Environment::GetSoundFolder()
	{
		return GetCurrentFolder() + L"\\..\\..\\data\\audio\\";
		//return GetCurrentFolder() + L"audio\\";
	}

    const Core::String Environment::GetShaderFolder()
	{
#ifdef __gnu_linux__
        return GetCurrentFolder() + L"/../../data/shaders/";
#else
        return GetCurrentFolder() + L"\\..\\..\\data\\shaders\\";
#endif
	}
	
    const Core::String Environment::GetArmatureFolder()
	{
		return GetCurrentFolder() + L"\\..\\..\\data\\armatures\\";
		//return GetCurrentFolder() + L"armatures\\";
	}

    const Core::String Environment::GetWeaponFolder()
	{
		return GetCurrentFolder() + L"\\..\\..\\data\\weapons\\";
		//return GetCurrentFolder() + L"weapons\\";
	}

    const Core::String Environment::GetOpenCLFolder()
	{
		return GetCurrentFolder() + L"\\..\\..\\data\\opencl\\";
		//return GetCurrentFolder() + L"weapons\\";
	}
}
PUNK_ENGINE_END
