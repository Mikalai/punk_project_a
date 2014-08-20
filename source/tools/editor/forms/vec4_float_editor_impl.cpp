#include "vec4_float_editor_impl.h"
#include <math/tuple.h>
#include <tools/editor/common.h>

PUNK_ENGINE_BEGIN
namespace Tools {
	Vec4FloatEditorImpl::Vec4FloatEditorImpl(wxWindow* parent)
		:
		Vec4FloatEditor(parent)
	{}

	Vec4FloatEditorImpl::~Vec4FloatEditorImpl() {
		m_value->UnsubscribeOnValueChanged(this);
	}

	void Vec4FloatEditorImpl::OnXChanged(wxCommandEvent& event) {
		double v;
		if (m_x->GetValue().ToDouble(&v)) {
			auto value = m_value->Get();			
			value.X() = (float)v;
			m_value->Set(value);
		}
	}

	void Vec4FloatEditorImpl::OnYChanged(wxCommandEvent& event) {
		double v;
		if (m_y->GetValue().ToDouble(&v)) {
			auto value = m_value->Get();
			value.Y() = (float)v;
			m_value->Set(value);
		}
	}

	void Vec4FloatEditorImpl::OnZChanged(wxCommandEvent& event) {
		double v;
		if (m_z->GetValue().ToDouble(&v)) {
			auto value = m_value->Get();
			value.Z() = (float)v;
			m_value->Set(value);
		}
	}

	void Vec4FloatEditorImpl::OnWChanged(wxCommandEvent& event) {
		double v;
		if (m_w->GetValue().ToDouble(&v)) {
			auto value = m_value->Get();
			value.W() = (float)v;
			m_value->Set(value);
		}
	}

	void Vec4FloatEditorImpl::SetSourceValue(const Core::String& name, Core::ValueMonitor<Math::vec4>* value) {
		m_value = value;
		UpdateGui(*m_value);		

		m_name->SetLabelText(Common::PunkStringToWxString(name));
		m_value->SubscribeOnValueChanged({ new Core::Action < Vec4FloatEditorImpl, const Math::vec4& > { this, &Vec4FloatEditorImpl::UpdateGui }, Core::DestroyObject });
	}

	void Vec4FloatEditorImpl::UpdateGui(const Math::vec4& value) {
		m_x->SetValue(wxString::Format(wxT("%f"), value.X()));
		m_y->SetValue(wxString::Format(wxT("%f"), value.Y()));
		m_z->SetValue(wxString::Format(wxT("%f"), value.Z()));
		m_w->SetValue(wxString::Format(wxT("%f"), value.W()));
	}
}
PUNK_ENGINE_END