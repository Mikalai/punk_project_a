#include "quat_float_editor_impl.h"
#include <math/tuple.h>
#include <tools/editor/common.h>


PUNK_ENGINE_BEGIN
namespace Tools {
	QuatFloatEditorImpl::QuatFloatEditorImpl(wxWindow* parent)
		:
		QuatFloatEditor(parent)
	{

	}

	void QuatFloatEditorImpl::OnWChanged(wxCommandEvent& event)
	{
		double v;
		if (m_w->GetValue().ToDouble(&v)) {
			m_value->W() = (float)v;
		}
	}

	void QuatFloatEditorImpl::OnXChanged(wxCommandEvent& event)
	{
		double v;
		if (m_x->GetValue().ToDouble(&v)) {
			m_value->X() = (float)v;
		}

	}

	void QuatFloatEditorImpl::OnYChanged(wxCommandEvent& event)
	{
		double v;
		if (m_y->GetValue().ToDouble(&v)) {
			m_value->Y() = (float)v;
		}

	}

	void QuatFloatEditorImpl::OnZChanged(wxCommandEvent& event)
	{
		double v;
		if (m_z->GetValue().ToDouble(&v)) {
			m_value->Z() = (float)v;
		}

	}

	void QuatFloatEditorImpl::SetSourceValue(const Core::String& name, Math::quat* value) {
		m_value = value;
		m_x->SetValue(wxString::Format(wxT("%f"), value->X()));
		m_y->SetValue(wxString::Format(wxT("%f"), value->Y()));
		m_z->SetValue(wxString::Format(wxT("%f"), value->Z()));
		m_w->SetValue(wxString::Format(wxT("%f"), value->W()));

		m_name->SetLabelText(Common::PunkStringToWxString(name));
	}
}
PUNK_ENGINE_END