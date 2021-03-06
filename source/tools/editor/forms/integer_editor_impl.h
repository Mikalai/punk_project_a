#ifndef __integer_editor_impl__
#define __integer_editor_impl__

/**
@file
Subclass of IntegerEditor, which is generated by wxFormBuilder.
*/

#include "forms.h"
#include <config.h>
#include <core/value_monitor.h>
#include <string/module.h>

//// end generated include

PUNK_ENGINE_BEGIN
namespace Tools {
	/** Implementing IntegerEditor */
	class IntegerEditorImpl : public IntegerEditor
	{
	protected:
		// Handlers for IntegerEditor events.
		void OnValueChanged(wxCommandEvent& event);
	public:
		/** Constructor */
		IntegerEditorImpl(wxWindow* parent);
		virtual ~IntegerEditorImpl();
		//// end generated class members
		void SetSourceValue(const Core::String& name, Core::ValueMonitor<int>* value);
		void UpdateGui(const int& value);
	private:
		Core::ValueMonitor<int>* m_int;
	};
}
PUNK_ENGINE_END

#endif // __integer_editor_impl__
