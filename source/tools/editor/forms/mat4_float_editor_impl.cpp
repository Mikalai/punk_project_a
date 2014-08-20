#include "mat4_float_editor_impl.h"
#include <math/matrix.h>
#include <tools/editor/common.h>

PUNK_ENGINE_BEGIN
namespace Tools {
	Mat4FloatEditorImpl::Mat4FloatEditorImpl(wxWindow* parent)
		:
		Mat4FloatEditor(parent)
	{}

	Mat4FloatEditorImpl::~Mat4FloatEditorImpl() {
		m_value->UnsubscribeOnValueChanged((void*)this);
	}

	void Mat4FloatEditorImpl::On0Changed(wxCommandEvent& event)
	{
		double v;
		if (m_0->GetValue().ToDouble(&v)) {
			auto m = m_value->Get();
			m.at(0) = (float)v;
			m_value->Set(m);
		}
	}

	void Mat4FloatEditorImpl::On4Changed(wxCommandEvent& event)
	{
		double v;
		if (m_4->GetValue().ToDouble(&v)) {
			auto m = m_value->Get();
			m.at(4) = (float)v;
			m_value->Set(m);
		}
	}

	void Mat4FloatEditorImpl::On8Changed(wxCommandEvent& event)
	{
		double v;
		if (m_8->GetValue().ToDouble(&v)) {
			auto m = m_value->Get();
			m.at(8) = (float)v;
			m_value->Set(m);
		}
	}

	void Mat4FloatEditorImpl::On12Changed(wxCommandEvent& event)
	{
		double v;
		if (m_12->GetValue().ToDouble(&v)) {
			auto m = m_value->Get();
			m.at(12) = (float)v;
			m_value->Set(m);
		}
	}

	void Mat4FloatEditorImpl::On1Changed(wxCommandEvent& event)
	{
		double v;
		if (m_1->GetValue().ToDouble(&v)) {
			auto m = m_value->Get();
			m.at(1) = (float)v;
			m_value->Set(m);
		}
	}

	void Mat4FloatEditorImpl::On5Changed(wxCommandEvent& event)
	{
		double v;
		if (m_5->GetValue().ToDouble(&v)) {
			auto m = m_value->Get();
			m.at(5) = (float)v;
			m_value->Set(m);
		}
	}

	void Mat4FloatEditorImpl::On9Changed(wxCommandEvent& event)
	{
		double v;
		if (m_9->GetValue().ToDouble(&v)) {
			auto m = m_value->Get();
			m.at(9) = (float)v;
			m_value->Set(m);
		}
	}

	void Mat4FloatEditorImpl::On13Changed(wxCommandEvent& event)
	{
		double v;
		if (m_13->GetValue().ToDouble(&v)) {
			auto m = m_value->Get();
			m.at(13) = (float)v;
			m_value->Set(m);
		}
	}

	void Mat4FloatEditorImpl::On2Changed(wxCommandEvent& event)
	{
		double v;
		if (m_2->GetValue().ToDouble(&v)) {
			auto m = m_value->Get();
			m.at(2) = (float)v;
			m_value->Set(m);
		}
	}

	void Mat4FloatEditorImpl::On6Changed(wxCommandEvent& event)
	{
		double v;
		if (m_6->GetValue().ToDouble(&v)) {
			auto m = m_value->Get();
			m.at(6) = (float)v;
			m_value->Set(m);
		}
	}

	void Mat4FloatEditorImpl::On10Changed(wxCommandEvent& event)
	{
		double v;
		if (m_10->GetValue().ToDouble(&v)) {
			auto m = m_value->Get();
			m.at(10) = (float)v;
			m_value->Set(m);
		}
	}

	void Mat4FloatEditorImpl::On14Changed(wxCommandEvent& event)
	{
		double v;
		if (m_14->GetValue().ToDouble(&v)) {
			auto m = m_value->Get();
			m.at(14) = (float)v;
			m_value->Set(m);
		}
	}

	void Mat4FloatEditorImpl::On3Changed(wxCommandEvent& event)
	{
		double v;
		if (m_3->GetValue().ToDouble(&v)) {
			auto m = m_value->Get();
			m.at(3) = (float)v;
			m_value->Set(m);
		}
	}

	void Mat4FloatEditorImpl::On7Changed(wxCommandEvent& event)
	{
		double v;
		if (m_7->GetValue().ToDouble(&v)) {
			auto m = m_value->Get();
			m.at(7) = (float)v;
			m_value->Set(m);
		}
	}

	void Mat4FloatEditorImpl::On11Changed(wxCommandEvent& event)
	{
		double v;
		if (m_11->GetValue().ToDouble(&v)) {
			auto m = m_value->Get();
			m.at(11) = (float)v;
			m_value->Set(m);
		}
	}

	void Mat4FloatEditorImpl::On15Changed(wxCommandEvent& event)
	{
		double v;
		if (m_15->GetValue().ToDouble(&v)) {
			auto m = m_value->Get();
			m.at(15) = (float)v;
			m_value->Set(m);
		}
	}

	void Mat4FloatEditorImpl::SetSourceValue(const Core::String& name, Core::ValueMonitor<Math::mat4>* value) {
		m_value = value;
		UpdateGui(*m_value);
		
		m_name->SetLabelText(Common::PunkStringToWxString(name));
		m_value->SubscribeOnValueChanged({ new Core::Action < Mat4FloatEditorImpl, const Math::mat4& > { this, &Mat4FloatEditorImpl::UpdateGui }, Core::DestroyObject });
	}

	void Mat4FloatEditorImpl::UpdateGui(const Math::mat4& value) {
		m_0->SetValue(wxString::Format(wxT("%f"), value.at(0)));
		m_1->SetValue(wxString::Format(wxT("%f"), value.at(1)));
		m_2->SetValue(wxString::Format(wxT("%f"), value.at(2)));
		m_3->SetValue(wxString::Format(wxT("%f"), value.at(3)));
		m_4->SetValue(wxString::Format(wxT("%f"), value.at(4)));
		m_5->SetValue(wxString::Format(wxT("%f"), value.at(5)));
		m_6->SetValue(wxString::Format(wxT("%f"), value.at(6)));
		m_7->SetValue(wxString::Format(wxT("%f"), value.at(7)));
		m_8->SetValue(wxString::Format(wxT("%f"), value.at(8)));
		m_9->SetValue(wxString::Format(wxT("%f"), value.at(9)));
		m_10->SetValue(wxString::Format(wxT("%f"), value.at(10)));
		m_11->SetValue(wxString::Format(wxT("%f"), value.at(11)));
		m_12->SetValue(wxString::Format(wxT("%f"), value.at(12)));
		m_13->SetValue(wxString::Format(wxT("%f"), value.at(13)));
		m_14->SetValue(wxString::Format(wxT("%f"), value.at(14)));
		m_15->SetValue(wxString::Format(wxT("%f"), value.at(5)));
	}
}
PUNK_ENGINE_END
