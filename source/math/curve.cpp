#include <cstdint>
#include "vec3.h"
#include "curve.h"

namespace Punk {
	namespace Engine {
		namespace Math
		{
			Curve::Curve() {}

			void Curve::AddSpline(const Spline& value) {
				m_total_length = 0;
				m_splines.push_back(value);
				for (Spline& s : m_splines) {
					m_total_length += s.GetTotalLength();
				}
			}

            void Curve::AddSplines(const Splines &value) {
                m_splines.insert(m_splines.end(), value.begin(), value.end());
                m_total_length = 0;
                for (Spline& s : m_splines) {
                    m_total_length += s.GetTotalLength();
                }
            }

            auto Curve::GetSplines() const -> const Splines& {
                return m_splines;
            }

			const Math::vec3 Curve::At(float t) {
				//  fine spline
				float cur_t = 0;
				float prev_t = 0;
				int spline_index = -1;
				for (std::size_t i = 0; i != m_splines.size(); ++i) {
					prev_t = cur_t;
					Spline& s = m_splines[i];
					cur_t += s.GetTotalLength() / m_total_length;
					if (cur_t > t) {
						spline_index = i;
						break;
					}
				}
				if (spline_index == -1)
					return Math::vec3();

				float tt = (t - prev_t) / (cur_t - prev_t);
				WeightedPoint p = m_splines[spline_index].At(tt);
				return p.GetPoint().XYZ();
			}

			float Curve::GetTotalLength() const {
				return m_total_length;
			}			

            void Curve::Clear() {
                m_total_length = 0;
                m_splines.clear();
            }
		}
	}
}
