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

	Vec3FloatEditorImpl::~Vec3FloatEditorImpl() {
		m_value->UnsubscribeOnValueChanged(this);
	}
	
	void Vec3FloatEditorImpl::UpdateGui(const Math::vec3& value) {
		m_x->SetValue(wxString::Format(wxT("%f"), value.X()));
		m_y->SetValue(wxString::Format(wxT("%f"), value.Y()));
		m_z->SetValue(wxString::Format(wxT("%f"), value.Z()));
	}

	void Vec3FloatEditorImpl::SetSourceValue(const Core::String& name, Core::ValueMonitor<Math::vec3>* value) {
		m_value = value;
		UpdateGui(*value);

		m_name->SetLabelText(Common::PunkStringToWxString(name));
		m_value->SubscribeOnValueChanged({ new Core::Action < Vec3FloatEditorImpl, const Math::vec3& > { this, &Vec3FloatEditorImpl::UpdateGui}, Core::DestroyObject });
	}

	void Vec3FloatEditorImpl::OnXChanged(wxCommandEvent& event) {
		double v;
		if (m_x->GetValue().ToDouble(&v)) {
			m_value->Set({ (float)v, m_value->Get().Y(), m_value->Get().Z() });
		}
	}

	void Vec3FloatEditorImpl::OnYChanged(wxCommandEvent& event) {
		double v;
		if (m_y->GetValue().ToDouble(&v)) {
			m_value->Set({ m_value->Get().X(), (float)v, m_value->Get().Z() });
		}
	}

	void Vec3FloatEditorImpl::OnZChanged(wxCommandEvent& event) {
		double v;
		if (m_z->GetValue().ToDouble(&v)) {
			m_value->Set({ m_value->Get().X(), m_value->Get().Y(), (float)v });
		}
	}
}
PUNK_ENGINE_END