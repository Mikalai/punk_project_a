#include <config.h>
#include <wx/wfstream.h>
#include <wx/filedlg.h>
#include <wx/fileconf.h>
#include <system/module/module.h>
#include "common.h"
#include "forms/forms.h"

PUNK_ENGINE_BEGIN
namespace Tools {

	void ModuleManagerDialog::OnModuleAdd(wxCommandEvent& event) {
		wxFileDialog * openFileDialog = new wxFileDialog(this);

		if (openFileDialog->ShowModal() == wxID_OK){
			wxString filename = openFileDialog->GetFilename();
			auto module = System::LoadPunkModule(filename.wc_str());
		}

		m_loaded_modules_list->Clear();
		for (std::uint32_t i = 0, max_i = System::GetLoadedPunkModulesCount(); i < max_i; ++i) {
			auto module = System::GetLoadedPunkModule(i);
			m_loaded_modules_list->Insert(wxString((const wchar_t*)module->GetName().Data()), 0, (void**)module);
		}
	}

	void ModuleManagerDialog::OnInit(wxInitDialogEvent& event) {
		
		Common::LoadModules();

		m_loaded_modules_list->Clear();
		for (std::uint32_t i = 0, max_i = System::GetLoadedPunkModulesCount(); i < max_i; ++i) {
			auto module = System::GetLoadedPunkModule(i);
			m_loaded_modules_list->Insert(wxString((const wchar_t*)module->GetName().Data()), 0, (void**)module);
		}
		event.Skip();
	}

	void ModuleManagerDialog::OnModuleRemove(wxCommandEvent& event) {

	}

	void ModuleManagerDialog::OnOk(wxCommandEvent& event) {
		Close();
	}

	void ModuleManagerDialog::OnClose(wxCloseEvent& event) {
		Common::SaveModules();
		event.Skip();
	}

	void ModuleManagerDialog::OnItemSelected(wxCommandEvent& event) {
		int selected_item_index = event.GetSelection();
		System::IModule* module = (System::IModule*)m_loaded_modules_list->GetClientData(selected_item_index);
		m_name_value->SetLabelText((wchar_t*)module->GetName().Data());
		m_module_path_value->SetLabelText((wchar_t*)module->GetDescription().Data());
	}
}
PUNK_ENGINE_END
