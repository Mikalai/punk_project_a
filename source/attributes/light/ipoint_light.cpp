#include <system/factory/module.h>
#include "ipoint_light.h"

PUNK_ENGINE_BEGIN
namespace Attributes {

	class Point : public IPoint {
	public:

		virtual ~Point() {}

		// IObject		
		void QueryInterface(const Core::Guid& type, void** object) override {
			if (!object)
				return;
			*object = nullptr;

			if (type == Core::IID_IObject) {
				*object = (IPoint*)this;
				AddRef();
			}
			else if (type == IID_IPoint) {
				*object = (IPoint*)this;
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

		//	IPoint
		void SetColor(const Math::Color3& value) override {
			m_color = value;
		}

		const Math::Color3 GetColor() const override {
			return m_color;
		}

		void SetConstantAttenuation(const Math::realf& value) override {
			m_constant = value;
		}

		const Math::realf GetConstantAttenuation() const override {
			return m_constant;
		}

		void SetLinearAttenuation(const Math::realf& value) override {
			m_linear = value;
		}

		const Math::realf GetLinearAttenuation() const override {
			return m_linear;
		}

		void SetQuadraticsAttenuation(const Math::realf& value) override {
			m_quadratic = value;
		}

		const Math::realf GetQuadraticsAttenuation() const override {
			return m_quadratic;
		}

		void SetZFar(const Math::realf& value) override {
			m_zfar = value;
		}

		const Math::realf GetZFar() override {
			return m_zfar;
		}

	private:
		std::atomic<std::uint32_t> m_ref_count{ 0 };
		Math::Color3 m_color;
		Math::realf m_constant{ 1 };
		Math::realf m_linear{ 0 };
		Math::realf m_quadratic{ 0 };
		Math::realf m_zfar{ 0.0 };
	};

	PUNK_REGISTER_CREATOR(CLSID_Point, (System::CreateInstance<Point, IPoint>));
}
PUNK_ENGINE_END
