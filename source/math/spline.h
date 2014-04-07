#ifndef SPLINE_H
#define SPLINE_H

#include <vector>
#include "weighted_point.h"

namespace Punk {
	namespace Engine {
		namespace Math
		{
			class PUNK_ENGINE_API Spline
			{
			public:
				Spline();
				void AddPoint(const WeightedPoint& value);
				void AddPoints(const std::vector<WeightedPoint>& value);
				float GetTotalLength() const;

				/**
				 * @brief At return interpolated point
				 * @param t From 0 to 1
				 * @return
				 */
				const WeightedPoint At(float t);

                std::size_t GetPointsCount() const;
                const WeightedPoint& GetPoint(int index) const;

			private:
				void UpdateTotalLength();
			private:
				std::vector<WeightedPoint> m_points;
				float m_total_length;
			};
		}
	}
}

#endif // SPLINE_H
