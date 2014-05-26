#include <core/ifactory.h>
#include "text_attribute.h"

PUNK_ENGINE_BEGIN
namespace Attributes {
	void Text::QueryInterface(const Core::Guid& type, void** object) {
		Core::QueryInterface(this, type, object, { Core::IID_IObject, IID_IText });
	}

	const Core::String Text::GetText() const {
		return m_text;
	}
	void Text::SetText(const Core::String& value) {
		m_text = value;
	}

	PUNK_REGISTER_CREATOR(IID_IText, Core::CreateInstance<Text>);
}
PUNK_ENGINE_END
