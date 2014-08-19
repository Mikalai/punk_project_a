#include "mat2_float_editor_impl.h"
#include <math/matrix.h>
#include <tools/editor/common.h>

PUNK_ENGINE_BEGIN
namespace Tools {
	Mat2FloatEditorImpl::Mat2FloatEditorImpl(wxWindow* parent)
		:
		Mat2FloatEditor(parent)
	{

	}

	void Mat2FloatEditorImpl::On0Changed(wxCommandEvent& event)
	{
		double v;
		if (m_0->GetValue().ToDouble(&v)) {
			m_value->at(0) = (float)v;
		}
	}

	void Mat2FloatEditorImpl::On1Changed(wxCommandEvent& event)
	{
		double v;
		if (m_1->GetValue().ToDouble(&v)) {
			m_value->at(1) = (float)v;
		}
	}

	void Mat2FloatEditorImpl::On2Changed(wxCommandEvent& event)
	{
		double v;
		if (m_2->GetValue().ToDouble(&v)) {
			m_value->at(2) = (float)v;
		}
	}

	void Mat2FloatEditorImpl::On3Changed(wxCommandEvent& event)
	{
		double v;
		if (m_3->GetValue().ToDouble(&v)) {
			m_value->at(3) = (float)v;
		}
	}

	void Mat2FloatEditorImpl::SetSourceValue(const Core::String& name, Math::mat2* value) {
		m_value = value;
		m_0->SetValue(wxString::Format(wxT("%f"), value->at(0)));
		m_1->SetValue(wxString::Format(wxT("%f"), value->at(1)));
		m_2->SetValue(wxString::Format(wxT("%f"), value->at(2)));
		m_3->SetValue(wxString::Format(wxT("%f"), value->at(3)));

		m_name->SetLabelText(Common::PunkStringToWxString(name));
	}
}
PUNK_ENGINE_END
