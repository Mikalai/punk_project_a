#include "string_editor_impl.h"
#include <tools/editor/common.h>

PUNK_ENGINE_BEGIN
namespace Tools {
	StringEditorImpl::StringEditorImpl(wxWindow* parent)
		:
		StringEditor(parent)
	{}

	StringEditorImpl::~StringEditorImpl() {
		m_str->UnsubscribeOnValueChanged(this);
	}

	void StringEditorImpl::OnValueChanged(wxCommandEvent& event)
	{
		double v;
		m_str->Set(Common::WxStringToPunkString(m_value->GetValue()));
	}

	void StringEditorImpl::SetSourceValue(const Core::String& name, Core::ValueMonitor<Core::String>* value) {
		m_str = value;
		UpdateGui(*m_str);
		m_name->SetLabelText(Common::PunkStringToWxString(name));
		m_str->SubscribeOnValueChanged({ new Core::Action < StringEditorImpl, const Core::String& > { this, &StringEditorImpl::UpdateGui }, Core::DestroyObject });
	}

	void StringEditorImpl::UpdateGui(const Core::String& value) {
		m_value->SetValue(Common::PunkStringToWxString(value));
	}
}
PUNK_ENGINE_END