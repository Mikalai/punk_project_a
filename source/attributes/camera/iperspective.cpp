#include <system/factory/module.h>
#include "iperspective.h"
#include "iprojection.h"

PUNK_ENGINE_BEGIN
namespace Attributes {

	class Perspective : public IPerspective, public IProjection {
	public:
		virtual ~Perspective() {}

		// IObject		
		void QueryInterface(const Core::Guid& type, void** object) override {
			if (!object)
				return;
			*object = nullptr;

			if (type == Core::IID_IObject) {
				*object = (IPerspective*)this;
				AddRef();
			}
			else if (type == IID_IPerspective) {
				*object = (IPerspective*)this;
				AddRef();
			}
			else if (type == IID_IProjection) {
				*object = (IProjection*)this;
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

		//	IPerspective
		void SetFovX(const Math::radf& value) override {
			m_fov_x = value;
			if (m_fov_y)
				m_aspect = m_fov_x / m_fov_y;
		}
		
		const Math::radf& GetFovX() const override {
			return m_fov_x;
		}

		void SetFovY(const Math::radf& value) override {
			m_fov_y = value;
			if (m_fov_x)
				m_aspect = m_fov_x / m_fov_y;
		}

		const Math::radf& GetFovY() const override {
			return m_fov_y;
		}

		void SetAspectRatio(const Math::realf& value) override {
			m_aspect = value;
			if (m_fov_x)
				m_fov_y = m_fov_x / m_aspect.GetValue();
			else if (m_fov_y)
				m_fov_x = m_fov_y * m_aspect.GetValue();
		}

		const Math::realf& GetAspectRatio() const override {
			return m_aspect;
		}

		void SetZNear(const Math::realf& value) override {
			m_znear = value;
		}

		const Math::realf& GetZNear() const override {
			return m_znear;
		}

		void SetZFar(const Math::realf& value) override {
			m_zfar = value;
		}

		const Math::realf& GetZFar() const override {
			return m_zfar;
		}
	private:
		std::atomic<std::uint32_t> m_ref_count{ 0 };
		Math::radf m_fov_x;
		Math::radf m_fov_y;
		Math::realf m_aspect;
		Math::realf m_znear;
		Math::realf m_zfar;
	};

	PUNK_REGISTER_CREATOR(CLSID_Perspective, (System::CreateInstance<Perspective, IPerspective>));
}
PUNK_ENGINE_END
