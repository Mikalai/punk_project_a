#ifndef _H_PUNK_PERLIN_NOISE
#define _H_PUNK_PERLIN_NOISE

#include <config.h>
#include <core/iobject.h>

PUNK_ENGINE_BEGIN
namespace Math {

	DECLARE_PUNK_GUID(IID_INoiseGenerator, "B718607C-3888-452A-AB4A-5728CC7BA111");
	DECLARE_PUNK_GUID(CLSID_NoiseGenerator, "FE9BD650-4D31-422B-92E9-113AC838DBF1");

	class INoiseGenerator;

	namespace __private {
		extern "C" PUNK_ENGINE_API INoiseGenerator* CreateNoiseGenerator();
	}

	class INoiseGenerator : public Core::IObject {
	public:
		virtual void Initialize(unsigned seed) = 0;
		virtual void SetOctavesCount(int value) = 0;
		virtual void SetPersistance(double value) = 0;
		virtual int GetOctavesCount() const = 0;
		virtual double GetPersistance() const = 0;

		virtual double Noise1D(int x) = 0;
		virtual double SmoothedNoise1D(int x) = 0;
		virtual double InterpolatedNoise1D(double x) = 0;
		virtual double PerlinNoise1D(double x) = 0;

		virtual double Noise2D(int x, int y) = 0;
		virtual double SmoothedNoise2D(int x, int y) = 0;
		virtual double InterpolatedNoise2D(double x, double y) = 0;
		virtual double PerlinNoise2D(double x, double y) = 0;

		virtual double Noise3D(int x, int y, int z) = 0;
		virtual double SmoothedNoise3D(int x, int y, int z) = 0;
		virtual double InterpolatedNoise3D(double x, double y, double z) = 0;
		virtual double PerlinNoise3D(double x, double y, double z) = 0;

		virtual double Noise4D(int x, int y, int z, int w) = 0;
		virtual double SmoothedNoise4D(int x, int y, int z, int w) = 0;
		virtual double InterpolatedNoise4D(double x, double y, double z, double w) = 0;
		virtual double PerlinNoise4D(double x, double y, double z, double w) = 0;

		virtual void GenerateHeightMap(double offset_x, double offset_y, double dim_x, double dim_y, int width, int height, float* data, int octave_count) = 0;
		virtual void GenerateSphericalHeightMap(double min_l, double min_b, double max_l, double max_b, int with, int height, float* data, int octave_count) = 0;

		static INoiseGenerator* Create() {
			return __private::CreateNoiseGenerator();
		}
	};
}
PUNK_ENGINE_END

#endif
