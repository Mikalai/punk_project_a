#include <wx/layout.h>
#include "attribute_panel_impl.h"
#include "vec3_float_editor_impl.h"

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
	void AttributePanelImpl::AddIntegerEditor(const Core::String& name, int* value) {

	}

	void AttributePanelImpl::AddBooleanEditor(const Core::String& name, bool *value) {

	}

	void AttributePanelImpl::AddFloatEditor(const Core::String& name, float* value) {
	}
	
	void AttributePanelImpl::AddDoubleEditor(const Core::String& name, double* value) {
	}
	
	void AttributePanelImpl::AddStringEditor(const Core::String& name, Core::String* value) {
	}

	void AttributePanelImpl::AddVec4FloatEditor(const Core::String& name, Math::vec4* value) {
	}
	
	void AttributePanelImpl::AddVec3FloatEditor(const Core::String& name, Math::vec3* value) {
		auto panel = new Vec3FloatEditorImpl(this);
		panel->SetSourceValue(name, value);
		m_layout->Add(panel);
		m_layout->Layout();
	}
	
	void AttributePanelImpl::AddVec2FloatEditor(const Core::String& name, Math::vec2* value) {
	}

	void AttributePanelImpl::AddQuatFloatEditor(const Core::String& name, Math::quat* value) {
	}
	
	void AttributePanelImpl::AddMat4FloatEditor(const Core::String& name, Math::mat4* value) {
	}
	
	void AttributePanelImpl::AddMat3FloatEditor(const Core::String& name, Math::mat3* value) {
	}

	void AttributePanelImpl::AddMat2FloatEditor(const Core::String& name, Math::mat2* value) {
	}
}

PUNK_ENGINE_END