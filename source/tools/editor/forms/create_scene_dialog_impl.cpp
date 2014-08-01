#include "create_scene_dialog_impl.h"
#include <tools/editor/common.h>
#include <tools/editor/action_manager.h>
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
		
		EndModal(wxID_OK);
	}

	void CreateSceneDialogImpl::OnCancel(wxCommandEvent& event)
	{
		// TODO: Implement OnCancel		
		EndModal(wxID_CANCEL);
	}	
}
PUNK_ENGINE_END
