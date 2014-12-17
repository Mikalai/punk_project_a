#ifdef USE_NOISE
#include <noise.h>
#include <noiseutils.h>
#else
#include "math_error.h"
#endif // USE_NOISE

#include <memory>
#include <time.h>
#include <system/factory/module.h>
#include "random.h"
#include "inoise_generator.h"
#include "constants.h"
#include "interpolation.h"

PUNK_ENGINE_BEGIN
namespace Math
{
	class NoiseImpl : public INoiseGenerator {
	public:

		NoiseImpl() {
			time_t t;
			time(&t);
			m_rnd.SetSeed(t);
			m_perlin.SetSeed(int(t));
			m_perlin.SetOctaveCount(4);
			m_perlin.SetPersistence(0.25);
		}

		//	IObject
		void QueryInterface(const Core::Guid& type, void** object) override {
			if (!object)
				return;
			*object = nullptr;
			if (type == Core::IID_IObject) {
				*object = (INoiseGenerator*)this;
				AddRef();
			}
			else if (type == IID_INoiseGenerator) {
				*object = (INoiseGenerator*)this;
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

		//	INoiseGenerator
		void Initialize(unsigned seed) override {
			m_rnd.SetSeed(seed);
			m_perlin.SetSeed(seed);
			m_perlin.SetOctaveCount(4);
			m_perlin.SetPersistence(0.25);
		}

		double Noise1D(int x) override {
			m_rnd.SetSeed(int(m_rnd.Noise(x)*100000.0));
			return m_rnd.Uniform(-1.0, 1.0);
		}

		double SmoothedNoise1D(int x) override {
			return Noise1D(x) / 2.0f + Noise1D(x - 1) / 4.0f + Noise1D(x + 1) / 4.0f;
		}

		double InterpolatedNoise1D(double x) override {
			int int_x = int(x);

			double frac = x - int_x;

			double v1 = SmoothedNoise1D(int_x);
			double v2 = SmoothedNoise1D(int_x + 1);

			return cosine_interpolation(v1, v2, frac);
		}

		double PerlinNoise1D(double x) override {
			return m_perlin.GetValue(x, 0, 0);
			//double total override;
			//double p = m_persistence;
			//
			//for (int i override; i < m_max_octaves; i++)
			//{
			//	double freq = pow(2, (double)i);
			//	double amp = pow(p, (double)i);

			//	total += InterpolatedNoise1D(x * freq) * amp;
			//}
			//return total;
		}

		double Noise2D(int x, int y) override {
			x += 57 * y;
			m_rnd.SetSeed(int(m_rnd.Noise(x)*100000.0));
			return m_rnd.Uniform(-1.0, 1.0);
		}

		double SmoothedNoise2D(int x, int y) override {
			double corner = (Noise2D(x - 1, y - 1) + Noise2D(x + 1, y - 1) + Noise2D(x - 1, y + 1) + Noise2D(x + 1, y + 1)) / 16.0f;
			double sides = (Noise2D(x - 1, y) + Noise2D(x + 1, y) + Noise2D(x, y - 1) + Noise2D(x, y + 1)) / 8.0f;
			double center = Noise2D(x, y) / 4.0f;
			return corner + sides + center;
		}

		double InterpolatedNoise2D(double x, double y) override {
			int int_x = int(x);
			double frac_x = x - int_x;

			int int_y = int(y);
			double frac_y = y - int_y;

			double v1 = SmoothedNoise2D(int_x, int_y);
			double v2 = SmoothedNoise2D(int_x + 1, int_y);
			double v3 = SmoothedNoise2D(int_x, int_y + 1);
			double v4 = SmoothedNoise2D(int_x + 1, int_y + 1);

			double i1 = cosine_interpolation(v1, v2, frac_x);
			double i2 = cosine_interpolation(v3, v4, frac_x);

			return cosine_interpolation(i1, i2, frac_y);
		}

		double PerlinNoise2D(double x, double y) override {
			return m_perlin.GetValue(x, y, 2);
			/*double total override;
			double p = m_persistence;

			for (int i override; i < m_max_octaves; i++)
			{
			double freq = pow(2, (double)i);
			double amp = pow(p, (double)i);

			total += InterpolatedNoise2D(x * freq, y * freq) * amp;
			}
			return total;*/
		}

		double Noise3D(int x, int y, int z) override {
			x += 57 * y + 131 * z;
			m_rnd.SetSeed(int(m_rnd.Noise(x)*100000.0));
			return m_rnd.Uniform(-1.0, 1.0);
		}

		double SmoothedNoise3D(int x, int y, int z) override {
			double diag_corner = (Noise3D(x - 1, y - 1, z - 1) + Noise3D(x - 1, y + 1, z - 1) + Noise3D(x + 1, y + 1, z - 1) + Noise3D(x + 1, y - 1, z - 1)
				+ Noise3D(x - 1, y - 1, z + 1) + Noise3D(x - 1, y + 1, z + 1) + Noise3D(x + 1, y + 1, z + 1) + Noise3D(x + 1, y - 1, z + 1)) / 32.0f;

			double corner = (Noise3D(x - 1, y - 1, z) + Noise3D(x + 1, y - 1, z) + Noise3D(x - 1, y + 1, z) + Noise3D(x + 1, y + 1, z) +
				Noise3D(x, y - 1, z - 1) + Noise3D(x, y - 1, z + 1) + Noise3D(x, y + 1, z - 1) + Noise3D(x, y + 1, z + 1) +
				Noise3D(x - 1, y, z - 1) + Noise3D(x + 1, y, z - 1) + Noise3D(x - 1, y, z + 1) + Noise3D(x + 1, y, z + 1)) / 16.0f;

			double sides = (Noise3D(x - 1, y, z) + Noise3D(x + 1, y, z) + Noise3D(x, y - 1, z) + Noise3D(x, y + 1, z) + Noise3D(x, y, z - 1) + Noise3D(x, y, z + 1)) / 8.0f;
			double center = Noise3D(x, y, z) / 4.0f;
			return corner + sides + center + diag_corner;
		}

		double InterpolatedNoise3D(double x, double y, double z) override {
			int int_x = int(x);
			double frac_x = x - int_x;

			int int_y = int(y);
			double frac_y = y - int_y;

			int int_z = int(z);
			double frac_z = z - int_z;

			double v1 = SmoothedNoise3D(int_x, int_y, int_z);
			double v2 = SmoothedNoise3D(int_x + 1, int_y, int_z);
			double v3 = SmoothedNoise3D(int_x, int_y + 1, int_z);
			double v4 = SmoothedNoise3D(int_x + 1, int_y + 1, int_z);

			double v5 = SmoothedNoise3D(int_x, int_y, int_z + 1);
			double v6 = SmoothedNoise3D(int_x + 1, int_y, int_z + 1);
			double v7 = SmoothedNoise3D(int_x, int_y + 1, int_z + 1);
			double v8 = SmoothedNoise3D(int_x + 1, int_y + 1, int_z + 1);

			double i1 = cosine_interpolation(v1, v2, frac_x);
			double i2 = cosine_interpolation(v3, v4, frac_x);
			double i3 = cosine_interpolation(v5, v6, frac_x);
			double i4 = cosine_interpolation(v7, v8, frac_x);

			double ii1 = cosine_interpolation(i1, i2, frac_y);
			double ii2 = cosine_interpolation(i3, i4, frac_y);

			return cosine_interpolation(ii1, ii2, frac_z);
		}

		double PerlinNoise3D(double x, double y, double z) override {
			return m_perlin.GetValue(x, y, z);
			//double total override;
			//double p = m_persistence;
			//
			//for (int i override; i < m_max_octaves; i++)
			//{
			//	double freq = pow(2, (double)i);
			//	double amp = pow(p, (double)i);

			//	total += InterpolatedNoise3D(x * freq, y * freq, z * freq) * amp;
			//}
			//return total;
		}

		double Noise4D(int x, int y, int z, int w) override {
			return 0;
		}

		double SmoothedNoise4D(int x, int y, int z, int w) override {
			return 0;
		}

		double InterpolatedNoise4D(double x, double y, double z, double w) override {
			return 0;
		}

		double PerlinNoise4D(double x, double y, double z, double w) override {
			return 0;
		}

		void SetOctavesCount(int count) override {
			m_perlin.SetOctaveCount(count);
		}

		void SetPersistance(double value) override {
			m_perlin.SetPersistence(value);
		}

		int GetOctavesCount() const override {
			return m_perlin.GetOctaveCount();
		}

		double GetPersistance() const override {
			return m_perlin.GetPersistence();
		}

		void GenerateHeightMap(double offset_x, double offset_y, double dim_x, double dim_y, int width, int height, float* data, int octave_count) override {
			module::RidgedMulti mountainTerrain;
			module::Billow baseFlatTerrain;
			baseFlatTerrain.SetFrequency(2.0);

			module::ScaleBias flatTerrain;
			flatTerrain.SetSourceModule(0, baseFlatTerrain);
			flatTerrain.SetScale(0.125);
			flatTerrain.SetBias(-0.75);

			module::Perlin terrainType;
			terrainType.SetFrequency(0.5);
			terrainType.SetPersistence(0.25);
			terrainType.SetOctaveCount(octave_count);

			module::Select terrainSelector;
			terrainSelector.SetSourceModule(0, flatTerrain);
			terrainSelector.SetSourceModule(1, mountainTerrain);
			terrainSelector.SetControlModule(terrainType);
			terrainSelector.SetBounds(0, 1000);
			terrainSelector.SetEdgeFalloff(0.125);

			module::Turbulence finalTerrain;
			finalTerrain.SetSourceModule(0, terrainSelector);
			finalTerrain.SetFrequency(4.0);
			finalTerrain.SetPower(0.125);

			utils::NoiseMap heightMap;
			utils::NoiseMapBuilderPlane heightMapBuilder;
			heightMapBuilder.SetSourceModule(finalTerrain);
			heightMapBuilder.SetDestNoiseMap(heightMap);
			heightMapBuilder.SetDestSize(width, height);
			heightMapBuilder.SetBounds(offset_x, offset_x + dim_x, offset_y, offset_y + dim_y);
			heightMapBuilder.Build();

			memcpy(data, heightMap.GetSlabPtr(), width*height*sizeof(float));
		}

		void GenerateSphericalHeightMap(double min_l, double min_b, double max_l, double max_b, int width, int height, float* data, int octave_count) override {
			module::Perlin myModule;
			myModule.SetOctaveCount(octave_count);

			utils::NoiseMap heightMap;
			utils::NoiseMapBuilderSphere heightMapBuilder;
			heightMapBuilder.SetSourceModule(myModule);
			heightMapBuilder.SetDestNoiseMap(heightMap);
			heightMapBuilder.SetDestSize(width, height);
			heightMapBuilder.SetBounds(min_b, max_b, min_l, max_l);
			heightMapBuilder.Build();

			memcpy(data, heightMap.GetSlabPtr(), width*height*sizeof(float));			
		}

	private:
		std::atomic<std::uint32_t> m_ref_count{ 0 };
		module::Perlin m_perlin;
		Random m_rnd;
	};

	extern "C" PUNK_ENGINE_API INoiseGenerator* CreateNoiseGenerator() {
		INoiseGenerator* result = System::CreateInstance<INoiseGenerator>(CLSID_NoiseGenerator);
		return result;
	}

	PUNK_REGISTER_CREATOR(CLSID_NoiseGenerator, (System::CreateInstance<NoiseImpl, INoiseGenerator>));
}
PUNK_ENGINE_END
