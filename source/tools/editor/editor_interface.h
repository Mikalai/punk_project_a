#ifndef _H_EDITOR_INTERFACE
#define _H_EDITOR_INTERFACE

#include <core/value_monitor.h>
#include <core/iobject.h>
#include <string/module.h>
#include <math/forward.h>
#include <config.h>

PUNK_ENGINE_BEGIN
namespace Tools {

	DECLARE_PUNK_GUID(IID_IEditorParametersPanel, "811BF4CA-8DED-4B0C-B1E5-E05FCB7EF2FC");
	class IEditorParametersPanel : public Core::IObject {
	public:
		virtual void AddIntegerEditor(const Core::String& name, Core::ValueMonitor<int>* value) = 0;
		virtual void AddBooleanEditor(const Core::String& name, Core::ValueMonitor<bool> *value) = 0;
		virtual void AddFloatEditor(const Core::String& name, Core::ValueMonitor<float>* value) = 0;
		virtual void AddDoubleEditor(const Core::String& name, Core::ValueMonitor<double>* value) = 0;
		virtual void AddStringEditor(const Core::String& name, Core::ValueMonitor<Core::String>* value) = 0;
		virtual void AddVec4FloatEditor(const Core::String& name, Core::ValueMonitor<Math::vec4>* value) = 0;
		virtual void AddVec3FloatEditor(const Core::String& name, Core::ValueMonitor<Math::vec3>* value) = 0;
		virtual void AddVec2FloatEditor(const Core::String& name, Core::ValueMonitor<Math::vec2>* value) = 0;
		virtual void AddQuatFloatEditor(const Core::String& name, Core::ValueMonitor<Math::quat>* value) = 0;
		virtual void AddMat4FloatEditor(const Core::String& name, Core::ValueMonitor<Math::mat4>* value) = 0;
		virtual void AddMat3FloatEditor(const Core::String& name, Core::ValueMonitor<Math::mat3>* value) = 0;
		virtual void AddMat2FloatEditor(const Core::String& name, Core::ValueMonitor<Math::mat2>* value) = 0;
	};

	DECLARE_PUNK_GUID(IID_IEditableElement, "39F07922-156C-496F-9414-7BF6545A12DF");

	class IEditableElement : public Core::IObject {
	public:
		virtual virtual void AddToPanel(IEditorParametersPanel* panel) = 0;
	};
}
PUNK_ENGINE_END

#endif	//	_H_EDITOR_INTERFACE