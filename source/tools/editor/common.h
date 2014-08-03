#ifndef _H_COMMON
#define _H_COMMON

#include <wx/string.h>
#include <config.h>
#include <scene/module.h>
#include <loader/module.h>

PUNK_ENGINE_BEGIN
namespace Tools {

	class Common {
	public:
		static void LoadModules();
		static void SaveModules();
		static Core::Pointer<SceneModule::ISceneModule> GetSceneModule();
		static Core::Pointer<IoModule::IIoModule> GetIoModule();
		static const wxString PunkStringToWxString(const Core::String& value);
		static const Core::String WxStringToPunkString(const wxString& value);
	};
}
PUNK_ENGINE_END

#endif