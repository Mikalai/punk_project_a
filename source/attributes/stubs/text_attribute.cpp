#include <system/factory/module.h>
#include "itext_attribute.h"

PUNK_ENGINE_BEGIN
namespace Attributes {

	class PUNK_ENGINE_LOCAL Text : public IText {
	public:
		//	IObject
		void QueryInterface(const Core::Guid& type, void** object) override;
		std::uint32_t AddRef() override;
		std::uint32_t Release() override;

		//	IText
		const Core::String GetText() const override;
		void SetText(const Core::String& value) override;
	private:
		std::atomic<std::uint32_t> m_ref_count{ 0 };
		Core::String m_text;
	};

	void Text::QueryInterface(const Core::Guid& type, void** object) {
		Core::QueryInterface(this, type, object, { Core::IID_IObject, IID_IText });
	}

	std::uint32_t Text::AddRef() {
		return m_ref_count.fetch_add(1);
	}

	std::uint32_t Text::Release() {
		auto v = m_ref_count.fetch_sub(1) - 1;
		if (!v) {
			delete this;
		}
		return v;
	}

	const Core::String Text::GetText() const {
		return m_text;
	}
	void Text::SetText(const Core::String& value) {
		m_text = value;
	}

	PUNK_REGISTER_CREATOR(IID_IText, (System::CreateInstance<Text, IText>));
}
PUNK_ENGINE_END
