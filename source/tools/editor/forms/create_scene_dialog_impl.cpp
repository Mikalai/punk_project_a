#include "create_scene_dialog_impl.h"
#include <tools/editor/common.h>
#include <system/factory/module.h>

PUNK_ENGINE_BEGIN
namespace Tools {
	CreateSceneDialogImpl::CreateSceneDialogImpl(wxWindow* parent)
		:
		CreateSceneDialog(parent)
	{

	}

	void CreateSceneDialogImpl::OnOk(wxCommandEvent& event)
	{
		// TODO: Implement OnOk
		m_scene = System::CreateInstancePtr<SceneModule::IScene>(SceneModule::CLSID_Scene, SceneModule::IID_IScene);
		m_scene->SetName(Common::WxStringToPunkString(m_scene_name->GetValue()));
		EndModal(wxID_OK);
	}

	void CreateSceneDialogImpl::OnCancel(wxCommandEvent& event)
	{
		// TODO: Implement OnCancel		
		EndModal(wxID_CANCEL);
	}	
}
PUNK_ENGINE_END
