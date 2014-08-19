#include "mat3_float_editor_impl.h"
#include <math/matrix.h>
#include <tools/editor/common.h>

PUNK_ENGINE_BEGIN
namespace Tools {
	Mat3FloatEditorImpl::Mat3FloatEditorImpl(wxWindow* parent)
		:
		Mat3FloatEditor(parent)
	{

	}

	void Mat3FloatEditorImpl::On0Changed(wxCommandEvent& event)
	{
		double v;
		if (m_0->GetValue().ToDouble(&v)) {
			m_value->at(0) = (float)v;
		}
	}

	void Mat3FloatEditorImpl::On4Changed(wxCommandEvent& event)
	{
		double v;
		if (m_4->GetValue().ToDouble(&v)) {
			m_value->at(4) = (float)v;
		}
	}

	void Mat3FloatEditorImpl::On8Changed(wxCommandEvent& event)
	{
		double v;
		if (m_8->GetValue().ToDouble(&v)) {
			m_value->at(8) = (float)v;
		}
	}

	void Mat3FloatEditorImpl::On1Changed(wxCommandEvent& event)
	{
		double v;
		if (m_1->GetValue().ToDouble(&v)) {
			m_value->at(1) = (float)v;
		}
	}

	void Mat3FloatEditorImpl::On5Changed(wxCommandEvent& event)
	{
		double v;
		if (m_5->GetValue().ToDouble(&v)) {
			m_value->at(5) = (float)v;
		}
	}

	void Mat3FloatEditorImpl::On2Changed(wxCommandEvent& event)
	{
		double v;
		if (m_2->GetValue().ToDouble(&v)) {
			m_value->at(2) = (float)v;
		}
	}

	void Mat3FloatEditorImpl::On6Changed(wxCommandEvent& event)
	{
		double v;
		if (m_6->GetValue().ToDouble(&v)) {
			m_value->at(6) = (float)v;
		}
	}

	void Mat3FloatEditorImpl::On3Changed(wxCommandEvent& event)
	{
		double v;
		if (m_3->GetValue().ToDouble(&v)) {
			m_value->at(3) = (float)v;
		}
	}

	void Mat3FloatEditorImpl::On7Changed(wxCommandEvent& event)
	{
		double v;
		if (m_7->GetValue().ToDouble(&v)) {
			m_value->at(7) = (float)v;
		}
	}

	void Mat3FloatEditorImpl::SetSourceValue(const Core::String& name, Math::mat3* value) {
		m_value = value;
		m_0->SetValue(wxString::Format(wxT("%f"), value->at(0)));
		m_1->SetValue(wxString::Format(wxT("%f"), value->at(1)));
		m_2->SetValue(wxString::Format(wxT("%f"), value->at(2)));
		m_3->SetValue(wxString::Format(wxT("%f"), value->at(3)));
		m_4->SetValue(wxString::Format(wxT("%f"), value->at(4)));
		m_5->SetValue(wxString::Format(wxT("%f"), value->at(5)));
		m_6->SetValue(wxString::Format(wxT("%f"), value->at(6)));
		m_7->SetValue(wxString::Format(wxT("%f"), value->at(7)));
		m_8->SetValue(wxString::Format(wxT("%f"), value->at(8)));

		m_name->SetLabelText(Common::PunkStringToWxString(name));
	}
}
PUNK_ENGINE_END
