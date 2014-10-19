#ifndef __bool_editor_impl__
#define __bool_editor_impl__

/**
@file
Subclass of BooleanEditor, which is generated by wxFormBuilder.
*/

#include "forms.h"
#include <config.h>
#include <core/value_monitor.h>
#include <string/string.h>

//// end generated include

PUNK_ENGINE_BEGIN
namespace Tools {
	/** Implementing BooleanEditor */
	class BooleanEditorImpl : public BooleanEditor
	{
	protected:
		// Handlers for BooleanEditor events.
		void OnValueChanged(wxCommandEvent& event);
	public:
		/** Constructor */
		BooleanEditorImpl(wxWindow* parent);
		virtual ~BooleanEditorImpl();
		//// end generated class members
		void SetSourceValue(const Core::String& name, Core::ValueMonitor<bool>* value);
		void UpdateGui(const bool& value);
	private:
		Core::ValueMonitor<bool>* m_bool;
	};
}
PUNK_ENGINE_END

#endif // __bool_editor_impl__