#include <wx/layout.h>
#include "attribute_panel_impl.h"
#include "vec3_float_editor_impl.h"
#include "vec2_float_editor_impl.h"
#include "vec4_float_editor_impl.h"
#include "mat2_float_editor_impl.h"
#include "mat3_float_editor_impl.h"
#include "mat4_float_editor_impl.h"
#include "quat_float_editor_impl.h"
#include "float_editor_impl.h"
#include "string_editor_impl.h"
#include "double_editor_impl.h"
#include "bool_editor_impl.h"
#include "integer_editor_impl.h"

PUNK_ENGINE_BEGIN
namespace Tools {

	AttributePanelImpl::AttributePanelImpl(wxWindow* parent)
		: AttributePanel(parent)
	{}

	void AttributePanelImpl::QueryInterface(const Core::Guid& type, void** object) {		
		*object = nullptr;
	}

	std::uint32_t AttributePanelImpl::AddRef() {
		return 0;
	}

	std::uint32_t AttributePanelImpl::Release() {
		return 0;
	}

	//	IEditorParametersPanel
	void AttributePanelImpl::AddIntegerEditor(const Core::String& name, Core::ValueMonitor<int>* value) {
		auto panel = new IntegerEditorImpl(this);
		panel->SetSourceValue(name, value);
		m_layout->Add(panel, 0, wxEXPAND | wxALIGN_TOP, 0);
		m_layout->Layout();
	}

	void AttributePanelImpl::AddBooleanEditor(const Core::String& name, Core::ValueMonitor<bool> *value) {
		auto panel = new BooleanEditorImpl(this);
		panel->SetSourceValue(name, value);
		m_layout->Add(panel, 0, wxEXPAND | wxALIGN_TOP, 0);
		m_layout->Layout();
	}

	void AttributePanelImpl::AddFloatEditor(const Core::String& name, Core::ValueMonitor<float>* value) {
		auto panel = new FloatEditorImpl(this);
		panel->SetSourceValue(name, value);
		m_layout->Add(panel, 0, wxEXPAND | wxALIGN_TOP, 0);
		m_layout->Layout();
	}
	
	void AttributePanelImpl::AddDoubleEditor(const Core::String& name, Core::ValueMonitor<double>* value) {
		auto panel = new DoubleEditorImpl(this);
		panel->SetSourceValue(name, value);
		m_layout->Add(panel, 0, wxEXPAND | wxALIGN_TOP, 0);
		m_layout->Layout();
	}
	
	void AttributePanelImpl::AddStringEditor(const Core::String& name, Core::ValueMonitor<Core::String>* value) {
		auto panel = new StringEditorImpl(this);
		panel->SetSourceValue(name, value);
		m_layout->Add(panel, 0, wxEXPAND | wxALIGN_TOP, 0);
		m_layout->Layout();
	}

	void AttributePanelImpl::AddVec4FloatEditor(const Core::String& name, Core::ValueMonitor<Math::vec4>* value) {
		auto panel = new Vec4FloatEditorImpl(this);
		panel->SetSourceValue(name, value);
		m_layout->Add(panel, 0, wxEXPAND | wxALIGN_TOP, 0);
		m_layout->Layout();
	}
	
	void AttributePanelImpl::AddVec3FloatEditor(const Core::String& name, Core::ValueMonitor<Math::vec3>* value) {
		auto panel = new Vec3FloatEditorImpl(this);
		panel->SetSourceValue(name, value);
		m_layout->Add(panel, 0, wxEXPAND | wxALIGN_TOP, 0);
		m_layout->Layout();
	}
	
	void AttributePanelImpl::AddVec2FloatEditor(const Core::String& name, Core::ValueMonitor<Math::vec2>* value) {
		auto panel = new Vec2FloatEditorImpl(this);
		panel->SetSourceValue(name, value);
		m_layout->Add(panel, 0, wxEXPAND | wxALIGN_TOP, 0);
		m_layout->Layout();
	}

	void AttributePanelImpl::AddQuatFloatEditor(const Core::String& name, Core::ValueMonitor<Math::quat>* value) {
		auto panel = new QuatFloatEditorImpl(this);
		panel->SetSourceValue(name, value);
		m_layout->Add(panel, 0, wxEXPAND | wxALIGN_TOP, 0);
		m_layout->Layout();
	}
	
	void AttributePanelImpl::AddMat4FloatEditor(const Core::String& name, Core::ValueMonitor<Math::mat4>* value) {
		auto panel = new Mat4FloatEditorImpl(this);
		panel->SetSourceValue(name, value);
		m_layout->Add(panel, 0, wxEXPAND | wxALIGN_TOP, 0);
		m_layout->Layout();
	}
	
	void AttributePanelImpl::AddMat3FloatEditor(const Core::String& name, Core::ValueMonitor<Math::mat3>* value) {
		auto panel = new Mat3FloatEditorImpl(this);
		panel->SetSourceValue(name, value);
		m_layout->Add(panel, 0, wxEXPAND | wxALIGN_TOP, 0);
		m_layout->Layout();
	}

	void AttributePanelImpl::AddMat2FloatEditor(const Core::String& name, Core::ValueMonitor<Math::mat2>* value) {
		auto panel = new Mat2FloatEditorImpl(this);
		panel->SetSourceValue(name, value);
		m_layout->Add(panel, 0, wxEXPAND | wxALIGN_TOP, 0);
		m_layout->Layout();
	}
}

PUNK_ENGINE_END