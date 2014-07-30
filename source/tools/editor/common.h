#ifndef _H_COMMON
#define _H_COMMON

#include <config.h>
#include <scene/module.h>
#include <wx/string.h>

PUNK_ENGINE_BEGIN
namespace Tools {

	class Common {
	public:
		static void LoadModules();
		static void SaveModules();
		static Core::Pointer<SceneModule::ISceneModule> GetSceneModule();
		static const wxString PunkStringToWxString(const Core::String& value);
		static const Core::String WxStringToPunkString(const wxString& value);
	};
}
PUNK_ENGINE_END

#endif