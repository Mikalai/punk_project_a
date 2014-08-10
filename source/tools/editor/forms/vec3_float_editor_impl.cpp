#include <wx/validate.h>
#include <math/tuple.h>
#include <tools/editor/common.h>
#include "vec3_float_editor_impl.h"

PUNK_ENGINE_BEGIN
namespace Tools {
	Vec3FloatEditorImpl::Vec3FloatEditorImpl(wxWindow* parent)
		:
		Vec3FloatEditor(parent)
	{

	}

	void Vec3FloatEditorImpl::SetSourceValue(const Core::String& name, Math::vec3* value) {
		m_value = value;
		m_x->SetValue(wxString::Format(wxT("%f"), value->X()));
		m_y->SetValue(wxString::Format(wxT("%f"), value->Y()));
		m_z->SetValue(wxString::Format(wxT("%f"), value->Z()));

		m_name->SetLabelText(Common::PunkStringToWxString(name));
	}

	void Vec3FloatEditorImpl::OnXChanged(wxCommandEvent& event) {
		double v;
		if (m_x->GetValue().ToDouble(&v)) {
			m_value->X() = (float)v;
		}
	}

	void Vec3FloatEditorImpl::OnYChanged(wxCommandEvent& event) {
		double v;
		if (m_y->GetValue().ToDouble(&v)) {
			m_value->Y() = (float)v;
		}
	}

	void Vec3FloatEditorImpl::OnZChanged(wxCommandEvent& event) {
		double v;
		if (m_z->GetValue().ToDouble(&v)) {
			m_value->Z() = (float)v;
		}
	}

}
PUNK_ENGINE_END