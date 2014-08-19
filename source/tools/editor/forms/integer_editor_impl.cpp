#include "integer_editor_impl.h"
#include <tools/editor/common.h>

PUNK_ENGINE_BEGIN
namespace Tools {
	IntegerEditorImpl::IntegerEditorImpl(wxWindow* parent)
		:
		IntegerEditor(parent) {
	}

	void IntegerEditorImpl::OnValueChanged(wxCommandEvent& event) {
		long v;
		if (m_value->GetValue().ToLong(&v)) {
			*m_int = (int)v;
		}
	}

	void IntegerEditorImpl::SetSourceValue(const Core::String& name, int* value) {
		m_int = value;
		m_value->SetValue(wxString::Format(wxT("%d"), *m_int));
		m_name->SetLabelText(Common::PunkStringToWxString(name));
	}
}
PUNK_ENGINE_END
