#ifndef SPLINE_H
#define SPLINE_H

#include <vector>
#include "ispline.h"
#include "weighted_point.h"

namespace Punk {
	namespace Engine {
		namespace Math
		{
			class PUNK_ENGINE_LOCAL Spline : public ISpline
			{
			public:
				Spline();
				virtual ~Spline();
				void QueryInterface(const Core::Guid& type, void** object) override;
				void AddPoint(const WeightedPoint& value) override;
				void AddPoints(const std::vector<WeightedPoint>& value) override;
				float GetTotalLength() const override;
				const WeightedPoint At(float t) override;
				std::uint32_t GetPointsCount() const override;
				const WeightedPoint& GetPoint(int index) const override;

			private:
				void UpdateTotalLength();
			private:
				std::vector<WeightedPoint> m_points;
				float m_total_length;

				PUNK_OBJECT_DEFAULT_IMPL3(Spline)
			};
		}
	}
}

#endif // SPLINE_H
