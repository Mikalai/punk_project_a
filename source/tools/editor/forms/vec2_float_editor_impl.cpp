#include "vec2_float_editor_impl.h"
#include <math/tuple.h>
#include <tools/editor/common.h>

PUNK_ENGINE_BEGIN
namespace Tools {
	Vec2FloatEditorImpl::Vec2FloatEditorImpl(wxWindow* parent)
		:
		Vec2FloatEditor(parent)
	{}

	Vec2FloatEditorImpl::~Vec2FloatEditorImpl() {
		m_value->UnsubscribeOnValueChanged(this);
	}

	void Vec2FloatEditorImpl::OnXChanged(wxCommandEvent& event)
	{
		double v;
		if (m_x->GetValue().ToDouble(&v)) {
			auto value = m_value->Get();
			value.X() = (float)v;
			m_value->Set(value);

		}
	}

	void Vec2FloatEditorImpl::OnYChanged(wxCommandEvent& event)
	{
		double v;
		if (m_y->GetValue().ToDouble(&v)) {
			auto value = m_value->Get();
			value.Y() = (float)v;
			m_value->Set(value);
		}
	}

	void Vec2FloatEditorImpl::SetSourceValue(const Core::String& name, Core::ValueMonitor<Math::vec2>* value) {
		m_value = value;
		UpdateGui(*m_value);
		m_name->SetLabelText(Common::PunkStringToWxString(name));

		m_value->SubscribeOnValueChanged({ new Core::Action < Vec2FloatEditorImpl, const Math::vec2& > { this, &Vec2FloatEditorImpl::UpdateGui }, Core::DestroyObject });
	}

	void Vec2FloatEditorImpl::UpdateGui(const Math::vec2& value) {
		m_x->SetValue(wxString::Format(wxT("%f"), value.X()));
		m_y->SetValue(wxString::Format(wxT("%f"), value.Y()));
	}
}
PUNK_ENGINE_END