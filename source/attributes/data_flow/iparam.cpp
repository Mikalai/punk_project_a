#include <system/factory/module.h>
#include "iparam.h"

PUNK_ENGINE_BEGIN
namespace Attributes {

	class Param : public IParam {
	public:
		//	IObject
		void QueryInterface(const Core::Guid& type, void** object) override {
			if (!object)
				return;
			*object = nullptr;

			if (type == Core::IID_IObject) {
				*object = (IParam*)this;
				AddRef();
			}
			else if (type == IID_IParam) {
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

		//	IParam
		void SetName(const Core::String& value) override {
			m_name = value;
		}

		const Core::String& GetName() const override {
			return m_name;
		}

		void SetSid(const Core::String& value) override {
			m_sid = value;
		}

		const Core::String& GetSid() const override {
			return m_sid;
		}

		void SetType(ParamType value) override {
			m_type = value;
		}

		ParamType GetType() const override {
			return m_type;
		}

		void SetSemantic(ParamSemantic value) override {
			m_semantic = value;
		}

		ParamSemantic GetSemantic() const override {
			return m_semantic;
		}

	private:
		std::atomic<std::uint32_t> m_ref_count{ 0 };
		Core::String m_name;
		Core::String m_sid;
		ParamType m_type{ ParamType::Bad };
		ParamSemantic m_semantic{ ParamSemantic::Bad };
	};

	PUNK_REGISTER_CREATOR(CLSID_Param, (System::CreateInstance < Param, IParam>));
}
PUNK_ENGINE_END
