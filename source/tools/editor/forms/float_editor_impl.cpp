#include "float_editor_impl.h"
#include <tools/editor/common.h>

PUNK_ENGINE_BEGIN
namespace Tools {
	FloatEditorImpl::FloatEditorImpl(wxWindow* parent)
		:
		FloatEditor(parent)
	{

	}

	FloatEditorImpl::~FloatEditorImpl() {
		m_num->UnsubscribeOnValueChanged(this);
	}

	void FloatEditorImpl::OnValueChanged(wxCommandEvent& event)
	{
		double v;
		if (m_value->GetValue().ToDouble(&v)) {
			m_num->Set((float)v);
		}
	}

	void FloatEditorImpl::SetSourceValue(const Core::String& name, Core::ValueMonitor<float>* value) {
		m_num = value;
		UpdateGui(*m_num);
		m_name->SetLabelText(Common::PunkStringToWxString(name));
		m_num->SubscribeOnValueChanged({ new Core::Action < FloatEditorImpl, const float& > { this, &FloatEditorImpl::UpdateGui }, Core::DestroyObject });
	}

	void FloatEditorImpl::UpdateGui(const float& value) {
		m_value->SetValue(wxString::Format(wxT("%f"), m_num->Get()));
	}
}
PUNK_ENGINE_END
