#include <system/factory/module.h>
#include <math/inoise_generator.h>
#include <math/trigonometry.h>
#include "iterrain_data_provider.h"

PUNK_ENGINE_BEGIN
namespace Attributes {
	class GeneratedTerrainDataProvider : public ITerrainDataProvider {
	public:
		GeneratedTerrainDataProvider() {
			m_generator = System::CreateInstancePtr<Math::INoiseGenerator>(Math::CLSID_NoiseGenerator, Math::IID_INoiseGenerator);
		}

		//	IObject
		void QueryInterface(const Core::Guid& type, void** object) override {
			if (!object)
				return;
			*object = nullptr;
			if (type == Core::IID_IObject) {
				*object = (ITerrainDataProvider*)this;
				AddRef();
			} else if (type == IID_ITerrainDataProvider) {
				*object = (ITerrainDataProvider*)this;
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

		//	ITerrainDataProvider
		void SetDestinationBuffer(std::uint32_t width, std::uint32_t height, float* buffer) override {
			m_buffer_width = width;
			m_buffer_height = height;
			m_buffer = buffer;
		}

		void SetVisibleRange(float l_min, float b_min, float l_max, float b_max) override {
			m_l_min = l_min;
			m_l_max = l_max;
			m_b_min = b_min;
			m_b_max = b_max;
		}

		void SetDetailsLevel(int value) override {
			m_details = value;
		}

		void UpdateBuffer() {
			auto l_min = std::min(m_l_min, m_l_max);
			auto l_max = std::max(m_l_min, m_l_max);
			auto b_min = std::min(m_b_min, m_b_max);
			auto b_max = std::max(m_b_max, m_b_min);			

			m_generator->GenerateSphericalHeightMap(l_min, b_min, l_max, b_max, m_buffer_width, m_buffer_height, m_buffer, m_details);
			/*float step_l = (l_max - l_min) / (float)m_buffer_width;
			float step_b = (b_max - b_min) / (float)m_buffer_height;
			for (int x = 0; x < m_buffer_width; ++x) {
				for (int y = 0; y < m_buffer_height; ++y) {
					auto l = l_min + step_l * (float)x;
					auto b = b_min + step_b * (float)y;
					auto xx = Math::Cos(b)*Math::Cos(l);
					auto yy = Math::Cos(b)*Math::Sin(l);
					auto zz = Math::Sin(b);			
					float height = (float)m_generator->PerlinNoise3D(xx, yy, zz);
					m_buffer[x + y * m_buffer_width] = height;
				}
			}*/
		}

	private:
		std::atomic<std::uint32_t> m_ref_count{ 0 };
		float* m_buffer{ nullptr };
		std::uint32_t m_buffer_width{ 0 };
		std::uint32_t m_buffer_height{ 0 };
		float m_l_min{ 0 };
		float m_l_max{ 0 };
		float m_b_min{ 0 };
		float m_b_max{ 0 };
		int m_details{ 5 };
		Core::Pointer<Math::INoiseGenerator> m_generator{ nullptr, Core::DestroyObject };
	};

	PUNK_REGISTER_CREATOR(CLSID_GeneratedTerrainDataProvider, (System::CreateInstance < GeneratedTerrainDataProvider, ITerrainDataProvider>));
}
PUNK_ENGINE_END
