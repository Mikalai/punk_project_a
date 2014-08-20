#include "double_editor_impl.h"
#include <tools/editor/common.h>

PUNK_ENGINE_BEGIN
namespace Tools {
	DoubleEditorImpl::DoubleEditorImpl(wxWindow* parent)
		:
		DoubleEditor(parent)
	{}

	DoubleEditorImpl::~DoubleEditorImpl() {
		m_num->UnsubscribeOnValueChanged(this);
	}

	void DoubleEditorImpl::OnValueChanged(wxCommandEvent& event)
	{
		double v;
		if (m_value->GetValue().ToDouble(&v)) {
			m_num->Set((float)v);
		}
	}

	void DoubleEditorImpl::SetSourceValue(const Core::String& name, Core::ValueMonitor<double>* value) {
		m_num = value;		
		UpdateGui(*m_num);
		m_name->SetLabelText(Common::PunkStringToWxString(name));
		m_num->SubscribeOnValueChanged({ new Core::Action < DoubleEditorImpl, const double& > { this, &DoubleEditorImpl::UpdateGui }, Core::DestroyObject });
	}

	void DoubleEditorImpl::UpdateGui(const double& value) {
		m_value->SetValue(wxString::Format(wxT("%f"), m_num->Get()));
	}
}
PUNK_ENGINE_END
