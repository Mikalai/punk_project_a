#include <system/factory/ifactory.h>
#include <math/tuple.h>
#include "iaccessor.h"
#include "iparam.h"

PUNK_ENGINE_BEGIN
namespace Attributes {

	class AccessorImpl : public IAccessor {
	public:
		virtual ~AccessorImpl() {
		}

		//	IObject
		void QueryInterface(const Core::Guid& type, void** object) override {
			if (!object)
				return;
			*object = nullptr;

			if (type == Core::IID_IObject) {
				*object = (IAccessor*)this;
				AddRef();
			}
			else if (type == IID_IAccessor) {
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

		//	IAccessor
		void SetCount(std::uint32_t value) override {
			m_count = value;
		}

		std::uint32_t GetCount() const override {
			return m_count;
		}

		void SetSource(const Core::String& value) override {
			m_source = value;
		}

		const Core::String& GetSource() const override {
			return m_source;
		}

		void SetStride(std::uint32_t value) override {
			m_stride = value;
		}

		std::uint32_t GetStride() const override {
			return m_stride;
		}

		void SetOffset(std::uint32_t value) override {
			m_offset = value;
		}

		std::uint32_t GetOffset() const override {
			return m_offset;
		}

		std::uint32_t GetParamsCount() const override {
			return (std::uint32_t)m_params.size();
		}

		void SetParamsCount(std::uint32_t value) override {
			m_params.resize(value);
		}

		IParam* GetParam(std::uint32_t index) override {
			return m_params.at(index).get();
		}

		const IParam* GetParam(std::uint32_t index) const override {
			return m_params.at(index).get();
		}

		void SetParam(std::uint32_t index, Core::Pointer<IParam> value) {
			m_params[index] = value;
		}

		void AddParam(Core::Pointer<IParam> value) override {
			m_params.push_back(value);
		}

	private:
		std::atomic<std::uint32_t> m_ref_count{ 0 };
		std::vector<Core::Pointer<IParam>> m_params;
		Core::String m_source;
		std::uint32_t m_count{ 0 };
		std::uint32_t m_offset{ 0 };
		std::uint32_t m_stride{ 1 };
	};	

	PUNK_REGISTER_CREATOR(CLSID_Accessor, (System::CreateInstance<AccessorImpl, IAccessor>));
}
PUNK_ENGINE_END
