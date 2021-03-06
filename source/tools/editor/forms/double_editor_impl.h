#ifndef __double_editor_impl__
#define __double_editor_impl__

/**
@file
Subclass of DoubleEditor, which is generated by wxFormBuilder.
*/

#include "forms.h"
#include <config.h>
#include <core/value_monitor.h>
#include <string/string.h>
//// end generated include

PUNK_ENGINE_BEGIN
namespace Tools {
	/** Implementing DoubleEditor */
	class DoubleEditorImpl : public DoubleEditor
	{
	protected:
		// Handlers for DoubleEditor events.
		void OnValueChanged(wxCommandEvent& event);
	public:
		/** Constructor */
		DoubleEditorImpl(wxWindow* parent);
		virtual ~DoubleEditorImpl();
		//// end generated class members
		void SetSourceValue(const Core::String& name, Core::ValueMonitor<double>* value);
		void UpdateGui(const double& v);
	private:
		Core::ValueMonitor<double>* m_num; 
	};
}
PUNK_ENGINE_END

#endif // __double_editor_impl__
