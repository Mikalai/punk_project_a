#include "string_editor_impl.h"
#include <tools/editor/common.h>

PUNK_ENGINE_BEGIN
namespace Tools {
	StringEditorImpl::StringEditorImpl(wxWindow* parent)
		:
		StringEditor(parent)
	{

	}

	void StringEditorImpl::OnValueChanged(wxCommandEvent& event)
	{
		double v;
		*m_str = Common::WxStringToPunkString(m_value->GetValue());
	}

	void StringEditorImpl::SetSourceValue(const Core::String& name, Core::String* value) {
		m_str = value;
		m_value->SetValue(Common::PunkStringToWxString(*m_str));
		m_name->SetLabelText(Common::PunkStringToWxString(name));
	}
}
PUNK_ENGINE_END