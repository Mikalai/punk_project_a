#include <system/factory/module.h>
#include <string/buffer.h>
#include <core/iserializable.h>
#include "itext_attribute.h"

PUNK_ENGINE_BEGIN
namespace Attributes {

	class PUNK_ENGINE_LOCAL Text : public IText, public Core::ISerializable {
	public:
		//	IObject
		void QueryInterface(const Core::Guid& type, void** object) override {
			if (!object)
				return;
			if (Core::IID_IObject == type) {
				*object = (IText*)this;
				AddRef();
			} else if (IID_IText == type) {
				*object = (IText*)this;
				AddRef();
			}
			else if (Core::IID_ISerializable == type) {
				*object = (Core::ISerializable*)this;
				AddRef();
			}
		}

		std::uint32_t AddRef() override {
			return m_ref_count.fetch_add(1);
		}

		std::uint32_t Release() override {
			auto v = m_ref_count.fetch_sub(1) - 1;
			if (!v) {
				delete this;
			}
			return v;
		}

		//	IText
		const Core::String GetText() const override {
			return m_text;
		}
		
		void SetText(const Core::String& value) override {
			m_text = value;
		}

		//	ISerializable
		void Serialize(Core::Buffer& buffer) override {
			buffer.WriteBuffer(CLSID_Text.ToPointer(), sizeof(CLSID_Text));
			buffer.WriteString(m_text);
		}

		void Deserialize(Core::Buffer& buffer) override {
			m_text = buffer.ReadString();
		}

	private:
		std::atomic<std::uint32_t> m_ref_count{ 0 };
		Core::String m_text;
	};		

	PUNK_REGISTER_CREATOR(CLSID_Text, (System::CreateInstance<Text, IText>));
}
PUNK_ENGINE_END
