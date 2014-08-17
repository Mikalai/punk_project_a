#ifndef __vec3_float_editor_impl__
#define __vec3_float_editor_impl__

/**
@file
Subclass of Vec3FloatEditor, which is generated by wxFormBuilder.
*/

#include <config.h>
#include <math/forward.h>
#include "forms.h"

//// end generated include

PUNK_ENGINE_BEGIN
namespace Tools {
	/** Implementing Vec3FloatEditor */
	class Vec3FloatEditorImpl : public Vec3FloatEditor
	{
	public:
		/** Constructor */
		Vec3FloatEditorImpl(wxWindow* parent);
		//// end generated class members

		void OnXChanged(wxCommandEvent& event);
		void OnYChanged(wxCommandEvent& event);
		void OnZChanged(wxCommandEvent& event);
		void SetSourceValue(const Core::String& name, Math::vec3* value);

	private:
		Math::vec3* m_value;
	};
}
PUNK_ENGINE_END

#endif // __vec3_float_editor_impl__