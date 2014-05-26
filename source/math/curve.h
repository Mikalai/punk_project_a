#ifndef CURVE_H
#define CURVE_H

#include <vector>
#include "config.h"
#include "spline.h"
#include "icurve.h"

namespace Punk {
	namespace Engine {
		namespace Math {

			class PUNK_ENGINE_LOCAL Curve : public ICurve
			{
			public:
				typedef std::vector<ISpline*> Splines;
			public:
				Curve();
				virtual ~Curve();

				void QueryInterface(const Core::Guid& type, void** object) override;
				
				void AddSpline(ISpline* value) override;
				void AddSplines(const std::vector<ISpline*>& value) override;
				float GetTotalLength() const override;
				const Math::vec3 At(float t) override;
				std::uint32_t GetSplinesCount() const override;
				const ISpline* GetSpline(std::uint32_t index) const override;
				void Clear() override;

			private:
				Splines m_splines;
				float m_total_length;				

				PUNK_OBJECT_DEFAULT_IMPL(Curve);
			};			
		}
	}
}
#endif // CURVE_H
