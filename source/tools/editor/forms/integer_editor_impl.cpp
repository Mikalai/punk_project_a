#include "integer_editor_impl.h"
#include <tools/editor/common.h>

PUNK_ENGINE_BEGIN
namespace Tools {
	IntegerEditorImpl::IntegerEditorImpl(wxWindow* parent)
		:
		IntegerEditor(parent) {
	}

	IntegerEditorImpl::~IntegerEditorImpl() {
		m_int->UnsubscribeOnValueChanged(this);
	}

	void IntegerEditorImpl::OnValueChanged(wxCommandEvent& event) {
		long v;
		if (m_value->GetValue().ToLong(&v)) {
			m_int->Set((int)v);
		}
	}

	void IntegerEditorImpl::SetSourceValue(const Core::String& name, Core::ValueMonitor<int>* value) {
		m_int = value;
		UpdateGui(*m_int);
		m_name->SetLabelText(Common::PunkStringToWxString(name));
		m_int->SubscribeOnValueChanged({ new Core::Action < IntegerEditorImpl, const int& > { this, &IntegerEditorImpl::UpdateGui }, Core::DestroyObject });
	}

	void IntegerEditorImpl::UpdateGui(const int& value) {
		m_value->SetValue(wxString::Format(wxT("%d"), m_int->Get()));
	}
}
PUNK_ENGINE_END
