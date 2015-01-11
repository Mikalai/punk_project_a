#include <system/factory/module.h>
#include "ivertices.h"

PUNK_ENGINE_BEGIN
namespace Attributes {

	class Vertices : public IVertices {
	public:
		virtual ~Vertices() {}

		//	IObject
		void QueryInterface(const Core::Guid& type, void** object) override {
			if (!object)
				return;
			*object = nullptr;

			if (type == Core::IID_IObject) {
				*object = (IAccessor*)this;
				AddRef();
			}
			else if (type == IID_IVertices) {
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

		//	IVertices
		void SetId(const Core::String& value) override {
			m_id = value;
		}

		const Core::String GetId() const override {
			return m_id;
		}

		void SetName(const Core::String& value) override {
			m_name = value;
		}

		const Core::String GetName() const override {
			return m_name;
		}

		void AddInput(IInputPtr value) override {
			m_inputs.push_back(value);
		}

		std::uint32_t GetInputsCount() const override {
			return (std::uint32_t)m_inputs.size();
		}

		IInputPtr GetInput(std::uint32_t index) const override {
			return m_inputs.at(index);
		}

	private:
		std::atomic<std::uint32_t> m_ref_count{ 0 };
		Core::String m_id;
		Core::String m_name;
		std::vector<IInputPtr> m_inputs;
	};

	PUNK_REGISTER_CREATOR(CLSID_Vertices, (System::CreateInstance<Vertices, IVertices>));
}
PUNK_ENGINE_END
