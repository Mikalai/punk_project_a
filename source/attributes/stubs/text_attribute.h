#ifndef _H_TEXT_ATTRIBUTE
#define _H_TEXT_ATTRIBUTE

#include "itext_attribute.h"

PUNK_ENGINE_BEGIN
namespace Attributes {
	class PUNK_ENGINE_LOCAL Text : public IText {
	public:
		void QueryInterface(const Core::Guid& type, void** object) override;
		const Core::String GetText() const override;
		void SetText(const Core::String& value) override;
	private:
		Core::String m_text;

		PUNK_OBJECT_DEFAULT_IMPL(Text)
	};
}
PUNK_ENGINE_END

#endif	//	_H_TEXT_ATTRIBUTE