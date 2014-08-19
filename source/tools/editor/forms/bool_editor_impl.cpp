#include "bool_editor_impl.h"
#include <tools/editor/common.h>

PUNK_ENGINE_BEGIN
namespace Tools {
	BooleanEditorImpl::BooleanEditorImpl(wxWindow* parent)
		:
		BooleanEditor(parent)
	{

	}

	void BooleanEditorImpl::OnValueChanged(wxCommandEvent& event)
	{
		*m_bool = m_check_box->IsChecked();
	}

	void BooleanEditorImpl::SetSourceValue(const Core::String& name, bool* value) {
		m_bool = value;
		if (*m_bool)
			m_check_box->Set3StateValue(wxCHK_CHECKED);
		else
			m_check_box->Set3StateValue(wxCHK_UNCHECKED);
		m_name->SetLabelText(Common::PunkStringToWxString(name));
	}
}
PUNK_ENGINE_END
