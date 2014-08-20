#include "mat2_float_editor_impl.h"
#include <math/matrix.h>
#include <tools/editor/common.h>

PUNK_ENGINE_BEGIN
namespace Tools {
	Mat2FloatEditorImpl::Mat2FloatEditorImpl(wxWindow* parent)
		:
		Mat2FloatEditor(parent)
	{}

	Mat2FloatEditorImpl::~Mat2FloatEditorImpl() {
		m_value->UnsubscribeOnValueChanged(this);
	}

	void Mat2FloatEditorImpl::UpdateGui(const Math::mat2& value) {
		m_0->SetValue(wxString::Format(wxT("%f"), value.at(0)));
		m_1->SetValue(wxString::Format(wxT("%f"), value.at(1)));
		m_2->SetValue(wxString::Format(wxT("%f"), value.at(2)));
		m_3->SetValue(wxString::Format(wxT("%f"), value.at(3)));
	}

	void Mat2FloatEditorImpl::On0Changed(wxCommandEvent& event)
	{
		double v;
		if (m_0->GetValue().ToDouble(&v)) {
			auto m = m_value->Get();
			m.at(0) = (float)v;
			m_value->Set(m);
		}
	}

	void Mat2FloatEditorImpl::On1Changed(wxCommandEvent& event)
	{
		double v;
		if (m_1->GetValue().ToDouble(&v)) {
			auto m = m_value->Get();
			m.at(1) = (float)v;
			m_value->Set(m);
		}
	}

	void Mat2FloatEditorImpl::On2Changed(wxCommandEvent& event)
	{
		double v;
		if (m_2->GetValue().ToDouble(&v)) {
			auto m = m_value->Get();
			m.at(2) = (float)v;
			m_value->Set(m);
		}
	}

	void Mat2FloatEditorImpl::On3Changed(wxCommandEvent& event)
	{
		double v;
		if (m_3->GetValue().ToDouble(&v)) {
			auto m = m_value->Get();
			m.at(3) = (float)v;
			m_value->Set(m);
		}
	}

	void Mat2FloatEditorImpl::SetSourceValue(const Core::String& name, Core::ValueMonitor<Math::mat2>* value) {
		m_value = value;
		UpdateGui(*m_value);
		m_value->SubscribeOnValueChanged({ new Core::Action < Mat2FloatEditorImpl, const Math::mat2& > { this, &Mat2FloatEditorImpl::UpdateGui }, Core::DestroyObject });

		m_name->SetLabelText(Common::PunkStringToWxString(name));
	}
}
PUNK_ENGINE_END
