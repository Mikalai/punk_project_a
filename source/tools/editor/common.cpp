#include <wx/wfstream.h>
#include <wx/filedlg.h>
#include <wx/fileconf.h>
#include "common.h"
#include <system/module/module.h>
#include <loader/module.h>
#include <attributes/module.h>

PUNK_ENGINE_BEGIN
namespace Tools {

	static Core::Pointer<SceneModule::ISceneModule> g_scene_module;
	static Core::Pointer<IoModule::IIoModule> g_io_module;
	static Core::Pointer<Attributes::IAttributesModule> g_attributes_module;

	void Common::LoadModules() {
		wxFileInputStream stream("modules.ini");
		wxFileConfig config(stream);
		wxString key; wxString value;
		long index;
		bool has_entry = config.GetFirstEntry(key, index);
		while (has_entry) {
			value = config.Read(key, L"");
			{
				auto module = Core::Pointer<System::IModule>(System::LoadPunkModule(value.wc_str()), Core::DestroyObject);
				if (module) {
					if (!g_scene_module)
						g_scene_module = Core::QueryInterfacePtr<SceneModule::ISceneModule>(module, SceneModule::IID_ISceneModule);
					if (!g_io_module)
						g_io_module = Core::QueryInterfacePtr<IoModule::IIoModule>(module, IoModule::IID_IIoModule);
					if (!g_attributes_module)
						g_attributes_module = Core::QueryInterfacePtr<Attributes::IAttributesModule>(module, Attributes::IID_IAttributesModule);
				}
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

	Core::Pointer<IoModule::IIoModule> Common::GetIoModule() {
		return g_io_module;
	}

	const wxString Common::PunkStringToWxString(const Core::String& value) {
		return wxString((wchar_t*)value.Data(), value.Length());
	}
	
	const Core::String Common::WxStringToPunkString(const wxString& value) {
		return Core::String(value.wc_str());
	}

	Core::Pointer<Attributes::IAttributesManager> Common::GetAttributesManager() {
		if (g_attributes_module) {
			return g_attributes_module->GetAttributeManager();
		}
		return Core::Pointer < Attributes::IAttributesManager > {nullptr, Core::DestroyObject};
	}

	void Common::Clean() {
		g_attributes_module.reset(nullptr);
		g_io_module.reset(nullptr);
		g_scene_module.reset(nullptr);
	}
}
PUNK_ENGINE_END
