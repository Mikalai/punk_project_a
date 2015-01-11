#include <system/factory/module.h>
#include "iprimitive_list.h"

PUNK_ENGINE_BEGIN
namespace Attributes {

	class PrimitivesList : public IPrimitivesList {
	public:
		//	IObject
		void QueryInterface(const Core::Guid& type, void** object) override {
			if (!object)
				return;
			*object = nullptr;

			if (type == Core::IID_IObject) {
				*object = this;
				AddRef();
			}
			else if (type == IID_IPrimitivesList) {
				*object = this;
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

		//	IVertexCountList
		std::uint32_t GetSize() const override {
			return (std::uint32_t)m_array.size();
		}

		void SetSize(std::uint32_t value) override {
			m_array.resize(value);
		}

		std::uint32_t GetValue(std::uint32_t index) override {
			return m_array.at(index);
		}

		void AddValue(std::uint32_t value) override {
			m_array.push_back(value);
		}

	private:
		std::atomic<std::uint32_t> m_ref_count{ 0 };
		std::vector<std::uint32_t> m_array;
	};

	PUNK_REGISTER_CREATOR(CLSID_PrimitivesList, (System::CreateInstance<PrimitivesList, IPrimitivesList>));
}
PUNK_ENGINE_END
