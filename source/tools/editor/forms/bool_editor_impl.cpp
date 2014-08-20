#include "bool_editor_impl.h"
#include <tools/editor/common.h>

PUNK_ENGINE_BEGIN
namespace Tools {
	BooleanEditorImpl::BooleanEditorImpl(wxWindow* parent)
		:
		BooleanEditor(parent)
	{}

	BooleanEditorImpl::~BooleanEditorImpl() {
		m_bool->UnsubscribeOnValueChanged(this);
	}

	void BooleanEditorImpl::OnValueChanged(wxCommandEvent& event)
	{
		m_bool->Set(m_check_box->IsChecked());
	}

	void BooleanEditorImpl::SetSourceValue(const Core::String& name, Core::ValueMonitor<bool>* value) {
		m_bool = value;
		UpdateGui(*m_bool);
		m_name->SetLabelText(Common::PunkStringToWxString(name));

		m_bool->SubscribeOnValueChanged({ new Core::Action < BooleanEditorImpl, const bool& > { this, &BooleanEditorImpl::UpdateGui }, Core::DestroyObject });
	}

	void BooleanEditorImpl::UpdateGui(const bool& value) {
		if (value)
			m_check_box->Set3StateValue(wxCHK_CHECKED);
		else
			m_check_box->Set3StateValue(wxCHK_UNCHECKED);
	}
}
PUNK_ENGINE_END
