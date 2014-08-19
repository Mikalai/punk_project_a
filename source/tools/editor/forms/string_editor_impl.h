#ifndef __string_editor_impl__
#define __string_editor_impl__

/**
@file
Subclass of StringEditor, which is generated by wxFormBuilder.
*/

#include "forms.h"
#include <config.h>
#include <string/string.h>
//// end generated include

PUNK_ENGINE_BEGIN
namespace Tools {
	/** Implementing StringEditor */
	class StringEditorImpl : public StringEditor
	{
	protected:
		// Handlers for StringEditor events.
		void OnValueChanged(wxCommandEvent& event);
	public:
		/** Constructor */
		StringEditorImpl(wxWindow* parent);
		//// end generated class members
		void SetSourceValue(const Core::String& name, Core::String* value);
	private:
		Core::String* m_str;
	};
}
PUNK_ENGINE_END

#endif // __string_editor_impl__
