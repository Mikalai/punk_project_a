#include "vec4_float_editor_impl.h"
#include <math/tuple.h>
#include <tools/editor/common.h>

PUNK_ENGINE_BEGIN
namespace Tools {
	Vec4FloatEditorImpl::Vec4FloatEditorImpl(wxWindow* parent)
		:
		Vec4FloatEditor(parent)
	{

	}

	void Vec4FloatEditorImpl::OnXChanged(wxCommandEvent& event) {
		double v;
		if (m_x->GetValue().ToDouble(&v)) {
			m_value->X() = (float)v;
		}
	}

	void Vec4FloatEditorImpl::OnYChanged(wxCommandEvent& event) {
		double v;
		if (m_y->GetValue().ToDouble(&v)) {
			m_value->Y() = (float)v;
		}
	}

	void Vec4FloatEditorImpl::OnZChanged(wxCommandEvent& event) {
		double v;
		if (m_z->GetValue().ToDouble(&v)) {
			m_value->Z() = (float)v;
		}
	}

	void Vec4FloatEditorImpl::OnWChanged(wxCommandEvent& event) {
		double v;
		if (m_w->GetValue().ToDouble(&v)) {
			m_value->W() = (float)v;
		}
	}

	void Vec4FloatEditorImpl::SetSourceValue(const Core::String& name, Math::vec4* value) {
		m_value = value;
		m_x->SetValue(wxString::Format(wxT("%f"), value->X()));
		m_y->SetValue(wxString::Format(wxT("%f"), value->Y()));
		m_z->SetValue(wxString::Format(wxT("%f"), value->Z()));
		m_w->SetValue(wxString::Format(wxT("%f"), value->W()));

		m_name->SetLabelText(Common::PunkStringToWxString(name));
	}
}
PUNK_ENGINE_END