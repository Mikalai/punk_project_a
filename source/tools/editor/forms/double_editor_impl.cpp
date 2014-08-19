#include "double_editor_impl.h"
#include <tools/editor/common.h>

PUNK_ENGINE_BEGIN
namespace Tools {
	DoubleEditorImpl::DoubleEditorImpl(wxWindow* parent)
		:
		DoubleEditor(parent)
	{

	}

	void DoubleEditorImpl::OnValueChanged(wxCommandEvent& event)
	{
		double v;
		if (m_value->GetValue().ToDouble(&v)) {
			*m_num = (float)v;
		}
	}

	void DoubleEditorImpl::SetSourceValue(const Core::String& name, double* value) {
		m_num = value;
		m_value->SetValue(wxString::Format(wxT("%f"), *m_num));
		m_name->SetLabelText(Common::PunkStringToWxString(name));
	}
}
PUNK_ENGINE_END
