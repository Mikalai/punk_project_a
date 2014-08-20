#ifndef __float_editor_impl__
#define __float_editor_impl__

/**
@file
Subclass of FloatEditor, which is generated by wxFormBuilder.
*/

#include "forms.h"
#include <core/value_monitor.h>
#include <config.h>
#include <string/string.h>
//// end generated include

PUNK_ENGINE_BEGIN
namespace Tools {
	/** Implementing FloatEditor */
	class FloatEditorImpl : public FloatEditor
	{
	protected:
		// Handlers for FloatEditor events.
		void OnValueChanged(wxCommandEvent& event);
	public:
		/** Constructor */
		FloatEditorImpl(wxWindow* parent);
		virtual ~FloatEditorImpl();
		//// end generated class members
		void SetSourceValue(const Core::String& name, Core::ValueMonitor<float>* value);
		void UpdateGui(const float& value);
	private:
		Core::ValueMonitor<float>* m_num;
	};
}
PUNK_ENGINE_END

#endif // __float_editor_impl__
