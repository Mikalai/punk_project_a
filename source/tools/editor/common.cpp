#include <system/module/module.h>
#include <wx/wfstream.h>
#include <wx/filedlg.h>
#include <wx/fileconf.h>
#include "common.h"

PUNK_ENGINE_BEGIN
namespace Tools {

	static Core::Pointer<SceneModule::ISceneModule> g_scene_module;

	void Common::LoadModules() {
		wxFileInputStream stream("modules.ini");
		wxFileConfig config(stream);
		wxString key; wxString value;
		long index;
		bool has_entry = config.GetFirstEntry(key, index);
		while (has_entry) {
			value = config.Read(key, L"");
			auto module = Core::Pointer<System::IModule>(System::LoadPunkModule(value.wc_str()), Core::DestroyObject);
			if (module) {
				g_scene_module = Core::QueryInterfacePtr<SceneModule::ISceneModule>(module, SceneModule::IID_ISceneModule);
			}
			has_entry = config.GetNextEntry(key, index);
		}
	}

	void Common::SaveModules() {
		wxFileConfig config;
		for (std::uint32_t i = 0, max_i = System::GetLoadedPunkModulesCount(); i < max_i; ++i) {
			auto module = System::GetLoadedPunkModule(i);
			config.Write((wchar_t*)module->GetName().Data(), (const wchar_t*)module->GetFullpath().Data());
		}
		wxFileOutputStream stream("modules.ini");
		config.Save(stream);
	}

	Core::Pointer<SceneModule::ISceneModule> Common::GetSceneModule() {
		return g_scene_module;
	}

	const wxString Common::PunkStringToWxString(const Core::String& value) {
		return wxString((wchar_t*)value.Data(), value.Length());
	}
	
	const Core::String Common::WxStringToPunkString(const wxString& value) {
		return Core::String(value.wc_str());
	}
}
PUNK_ENGINE_END
