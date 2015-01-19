#include <system/factory/module.h>
#include "ipolylist.h"

PUNK_ENGINE_BEGIN
namespace Attributes {

	class PolyList : public IPolyList {
	public:
		virtual ~PolyList() {}

		//	IObject
		void QueryInterface(const Core::Guid& type, void** object) override {
			if (!object)
				return;
			*object = nullptr;

			if (type == Core::IID_IObject) {
				*object = this;
				AddRef();
			}
			else if (type == IID_IPolyList) {
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

		//	IPolyList
		void SetSize(std::uint32_t value) override {
			m_count = value;
		}
		std::uint32_t GetSize() const override {
			return m_count;
		}

		void SetMaterialRef(const Core::String& value) override {
			m_material = value;
		}

		const Core::String GetMaterialRef() const override {
			return m_material;
		}

		void SetVertexCountList(IVertexCountListPtr value) override {
			m_vertex = value;
		}

		const IVertexCountListPtr GetVertexCountList() const override {
			return m_vertex;
		}

		void AddInput(IInputSharedPtr value) override {
			m_inputs.push_back(value);
		}

		std::uint32_t GetInputsCount() const override {
			return (std::uint32_t)m_inputs.size();
		}

		IInputSharedPtr GetInput(std::uint32_t value) override {
			return m_inputs.at(value);
		}

		void SetPrimitivesList(IPrimitivesListPtr value) override {
			m_primitives = value;
		}

		IPrimitivesListPtr GetPrimitivesList() const override {
			return m_primitives;
		}

	private:
		std::atomic<std::uint32_t> m_ref_count{ 0 };
		std::uint32_t m_count{ 0 };
		Core::String m_material;
		IVertexCountListPtr m_vertex;
		std::vector<IInputSharedPtr> m_inputs;
		IPrimitivesListPtr m_primitives;
	};

	PUNK_REGISTER_CREATOR(CLSID_PolyList, (System::CreateInstance<PolyList, IPolyList>));
}
PUNK_ENGINE_END