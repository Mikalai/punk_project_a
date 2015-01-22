#include <vector>
#include <system/factory/module.h>
#include "ilibrary_cameras.h"

PUNK_ENGINE_BEGIN
namespace Attributes {

	class LibraryCameras : public ILibraryCameras {
	public:

		virtual ~LibraryCameras() {}

		// IObject		
		void QueryInterface(const Core::Guid& type, void** object) override {
			if (!object)
				return;
			*object = nullptr;

			if (type == Core::IID_IObject) {
				*object = (ILibraryCameras*)this;
				AddRef();
			}
			else if (type == IID_ILibraryCameras) {
				*object = (ILibraryCameras*)this;
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

		//	ILibrary camera
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

		void AddCamera(ICamera2Ptr value) override {
			m_camera.push_back(value);
		}

		std::uint32_t GetCamerasCount() const override {
			return (std::uint32_t)m_camera.size();
		}

		ICamera2Ptr GetCamera(std::uint32_t index) const override {
			return m_camera.at(index);
		}

	private:
		std::atomic<std::uint32_t> m_ref_count{ 0 };
		Core::String m_id;
		Core::String m_name;
		std::vector<ICamera2Ptr> m_camera;
	};

	PUNK_REGISTER_CREATOR(CLSID_LibraryCameras, (System::CreateInstance<LibraryCameras, ILibraryCameras>));
}
PUNK_ENGINE_END
