#ifndef __create_scene_dialog_impl__
#define __create_scene_dialog_impl__

/**
@file
Subclass of CreateSceneDialog, which is generated by wxFormBuilder.
*/

#include <config.h>
#include <scene/module.h>
#include "forms.h"

//// end generated include

PUNK_ENGINE_BEGIN
namespace Tools {
	class CreateSceneDialogImpl : public CreateSceneDialog
	{
	protected:
		// Handlers for CreateSceneDialog events.
		void OnOk(wxCommandEvent& event);
		void OnCancel(wxCommandEvent& event);
	public:
		/** Constructor */
		CreateSceneDialogImpl(wxWindow* parent);
		//// end generated class members

		const wxString GetSceneName() {
			return m_scene_name->GetValue();
		}

	};
}
PUNK_ENGINE_END

#endif // __create_scene_dialog_impl__
