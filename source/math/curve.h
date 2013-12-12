#ifndef CURVE_H
#define CURVE_H

#include <vector>
#include "config.h"
#include "spline.h"

namespace Punk {
	namespace Engine {
		namespace Math {
			class PUNK_ENGINE_API Curve
			{
			public:
				typedef std::vector<Spline> Splines;
			public:
				Curve();

				void AddSpline(const Spline& value);
				float GetTotalLength() const;
				const Math::vec3 At(float t);

			private:
				Splines m_splines;
				float m_total_length;				
			};			
		}
	}
}
#endif // CURVE_H
