#ifndef __mat2_float_editor_impl__
#define __mat2_float_editor_impl__

/**
@file
Subclass of Mat2FloatEditor, which is generated by wxFormBuilder.
*/

#include "forms.h"
#include <config.h>
#include <core/value_monitor.h>
#include <math/forward.h>
#include <string/string.h>


//// end generated include

PUNK_ENGINE_BEGIN
namespace Tools {
	/** Implementing Mat2FloatEditor */
	class Mat2FloatEditorImpl : public Mat2FloatEditor
	{
	protected:
		// Handlers for Mat2FloatEditor events.
		void On0Changed(wxCommandEvent& event);
		void On2Changed(wxCommandEvent& event);
		void On1Changed(wxCommandEvent& event);
		void On3Changed(wxCommandEvent& event);
	public:
		/** Constructor */
		Mat2FloatEditorImpl(wxWindow* parent);
		virtual ~Mat2FloatEditorImpl();
		//// end generated class members
		void SetSourceValue(const Core::String& name, Core::ValueMonitor<Math::mat2>* value);
		void UpdateGui(const Math::mat2& value);
	private:
		Core::ValueMonitor<Math::mat2>* m_value;
	};
}
PUNK_ENGINE_END

#endif // __mat2_float_editor_impl__
