#include <system/factory/module.h>
#include "imesh.h"
#include "igeometry_element.h"

PUNK_ENGINE_BEGIN
namespace Attributes {

	class Mesh : public IMesh, public IGeometryElement {
	public:
		virtual ~Mesh() {}

		//	IObject
		void QueryInterface(const Core::Guid& type, void** object) override {
			if (!object)
				return;
			*object = nullptr;

			if (type == Core::IID_IObject) {
				*object = (IMesh*)this;
				AddRef();
			}
			else if (type == IID_IMesh) {
				*object = (IMesh*)this;
				AddRef();
			}
			else if (type == IID_IGeometryElement) {
				*object = (IGeometryElement*)this;
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

		//	IMesh
		void AddSource(ISourcePtr value) override {
			m_sources.push_back(value);
		}

		std::uint32_t GetSourcesCount() const override {
			return (std::uint32_t)m_sources.size();
		}

		ISourcePtr GetSource(std::uint32_t value) override {
			return m_sources.at(value);
		}

		void SetVertices(IVerticesPtr value) override {
			m_vertices = value;
		}

		IVerticesPtr GetVerices() const override {
			return m_vertices;
		}

		void AddPolylist(IPolyListPtr value) override {
			m_polylists.push_back(value);
		}

		std::uint32_t GetPolylistsCount() override {
			return (std::uint32_t)m_polylists.size();
		}

		IPolyListPtr GetPolylist(std::uint32_t value) override {
			return m_polylists.at(value);
		}

	private:
		std::atomic<std::uint32_t> m_ref_count{ 0 };
		std::vector<ISourcePtr> m_sources;
		IVerticesPtr m_vertices;
		std::vector<IPolyListPtr> m_polylists;
	};
	
	PUNK_REGISTER_CREATOR(CLSID_Mesh, (System::CreateInstance < Mesh, IMesh>));
}
PUNK_ENGINE_END