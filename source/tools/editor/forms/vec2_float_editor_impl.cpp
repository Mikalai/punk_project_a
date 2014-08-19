#include "vec2_float_editor_impl.h"
#include <math/tuple.h>
#include <tools/editor/common.h>

PUNK_ENGINE_BEGIN
namespace Tools {
	Vec2FloatEditorImpl::Vec2FloatEditorImpl(wxWindow* parent)
		:
		Vec2FloatEditor(parent)
	{

	}

	void Vec2FloatEditorImpl::OnXChanged(wxCommandEvent& event)
	{
		double v;
		if (m_x->GetValue().ToDouble(&v)) {
			m_value->X() = (float)v;
		}
	}

	void Vec2FloatEditorImpl::OnYChanged(wxCommandEvent& event)
	{
		double v;
		if (m_y->GetValue().ToDouble(&v)) {
			m_value->Y() = (float)v;
		}
	}

	void Vec2FloatEditorImpl::SetSourceValue(const Core::String& name, Math::vec2* value) {
		m_value = value;
		m_x->SetValue(wxString::Format(wxT("%f"), value->X()));
		m_y->SetValue(wxString::Format(wxT("%f"), value->Y()));

		m_name->SetLabelText(Common::PunkStringToWxString(name));
	}
}
PUNK_ENGINE_END