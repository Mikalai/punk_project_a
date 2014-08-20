#include "quat_float_editor_impl.h"
#include <math/tuple.h>
#include <tools/editor/common.h>


PUNK_ENGINE_BEGIN
namespace Tools {
	QuatFloatEditorImpl::QuatFloatEditorImpl(wxWindow* parent)
		:
		QuatFloatEditor(parent)
	{}

	QuatFloatEditorImpl::~QuatFloatEditorImpl() {
		m_value->UnsubscribeOnValueChanged(this);
	}

	void QuatFloatEditorImpl::OnWChanged(wxCommandEvent& event)
	{
		double v;
		if (m_w->GetValue().ToDouble(&v)) {
			auto q = m_value->Get();
			q.W() = (float)v;
			m_value->Set(q);
		}
	}

	void QuatFloatEditorImpl::OnXChanged(wxCommandEvent& event)
	{
		double v;
		if (m_x->GetValue().ToDouble(&v)) {
			auto q = m_value->Get();
			q.X() = (float)v;
			m_value->Set(q);
		}

	}

	void QuatFloatEditorImpl::OnYChanged(wxCommandEvent& event)
	{
		double v;
		if (m_y->GetValue().ToDouble(&v)) {
			auto q = m_value->Get();
			q.Y() = (float)v;
			m_value->Set(q);
		}

	}

	void QuatFloatEditorImpl::OnZChanged(wxCommandEvent& event)
	{
		double v;
		if (m_z->GetValue().ToDouble(&v)) {
			auto q = m_value->Get();
			q.Z() = (float)v;
			m_value->Set(q);
		}

	}

	void QuatFloatEditorImpl::SetSourceValue(const Core::String& name, Core::ValueMonitor<Math::quat>* value) {
		m_value = value;
		UpdateGui(*m_value);
		m_name->SetLabelText(Common::PunkStringToWxString(name));
		m_value->SubscribeOnValueChanged({ new Core::Action < QuatFloatEditorImpl, const Math::quat& > { this, &QuatFloatEditorImpl::UpdateGui }, Core::DestroyObject });
	}

	void QuatFloatEditorImpl::UpdateGui(const Math::quat& value) {
		m_x->SetValue(wxString::Format(wxT("%f"), value.X()));
		m_y->SetValue(wxString::Format(wxT("%f"), value.Y()));
		m_z->SetValue(wxString::Format(wxT("%f"), value.Z()));
		m_w->SetValue(wxString::Format(wxT("%f"), value.W()));

	}
}
PUNK_ENGINE_END