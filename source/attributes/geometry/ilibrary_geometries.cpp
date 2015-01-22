#include <vector>
#include <system/factory/module.h>
#include "ilibrary_geometries.h"

PUNK_ENGINE_BEGIN
namespace Attributes {

	class LibraryGeometries : public ILibraryGeometries {
	public:
		virtual ~LibraryGeometries() {}

		//	IObject
		void QueryInterface(const Core::Guid& type, void** object) override {
			if (!object)
				return;
			*object = nullptr;

			if (type == Core::IID_IObject) {
				*object = (ILibraryGeometries*)this;
				AddRef();
			}
			else if (type == IID_ILibraryGeometries) {
				*object = (ILibraryGeometries*)this;
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

		//	ILibraryGeometries
		void SetName(const Core::String& value) override {
			m_name = value;
		}

		const Core::String GetName() const override {
			return m_name;
		}

		void SetId(const Core::String& value) override {
			m_id = value;
		}

		const Core::String GetId() const override {
			return m_id;
		}

		void AddGeometry(IGeometry2Ptr value) override {
			m_geometry.push_back(value);
		}

		std::uint32_t GetGeometriesCount() const override {
			return (std::uint32_t)m_geometry.size();
		}

		IGeometry2Ptr GetGeometry(std::uint32_t index) override {
			return m_geometry.at(index);
		}

	private:
		std::atomic<std::uint32_t> m_ref_count{ 0 };
		Core::String m_name;
		Core::String m_id;
		std::vector<IGeometry2Ptr> m_geometry;
	};

	PUNK_REGISTER_CREATOR(CLSID_LibraryGeometries, (System::CreateInstance < LibraryGeometries, ILibraryGeometries>));
}
PUNK_ENGINE_END
