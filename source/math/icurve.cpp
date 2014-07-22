#include <vector>
#include <cstdint>
#include <system/factory/module.h>
#include "vec3.h"
#include "weighted_point.h"
#include "ispline.h"
#include "icurve.h"


PUNK_ENGINE_BEGIN
namespace Math
{
	class PUNK_ENGINE_LOCAL Curve : public ICurve
	{
	public:
		typedef std::vector<ISpline*> Splines;
	public:
		void QueryInterface(const Core::Guid& type, void** object) {
			Core::QueryInterface(this, type, object, { Core::IID_IObject, IID_ICurve });
		}

		std::uint32_t AddRef() {
			return m_ref_count.fetch_add(1);
		}

		std::uint32_t Release() {
			auto v = m_ref_count.fetch_sub(1) - 1;
			if (!v) {
				delete this;
			}
			return v;
		}

		Curve() {}

		~Curve() {
			while (!m_splines.empty()) {
				m_splines.back()->Release();
				m_splines.pop_back();
			}
		}
		void AddSpline(ISpline* value) {
			m_total_length = 0;
			m_splines.push_back(value);
			for (ISpline* s : m_splines) {
				m_total_length += s->GetTotalLength();
			}
		}

		void AddSplines(const std::vector<ISpline*>& value) {
			m_splines.insert(m_splines.end(), value.begin(), value.end());
			m_total_length = 0;
			for (ISpline* s : m_splines) {
				m_total_length += s->GetTotalLength();
			}
		}

		std::uint32_t GetSplinesCount() const {
			return (std::uint32_t)m_splines.size();
		}

		const ISpline* GetSpline(std::uint32_t index) const {
			return m_splines[index];
		}

		const point3d At(float t) {
			//  fine spline
			float cur_t = 0;
			float prev_t = 0;
			int spline_index = -1;
			for (std::size_t i = 0; i != m_splines.size(); ++i) {
				prev_t = cur_t;
				ISpline* s = m_splines[i];
				cur_t += s->GetTotalLength() / m_total_length;
				if (cur_t > t) {
					spline_index = (int)i;
					break;
				}
			}
			if (spline_index == -1)
				return{ 0, 0, 0 };

			float tt = (t - prev_t) / (cur_t - prev_t);
			WeightedPoint p = m_splines[spline_index]->At(tt);
			return p.GetPoint();
		}

		float GetTotalLength() const {
			return m_total_length;
		}

		void Clear() {
			m_total_length = 0;
			m_splines.clear();
		}

	private:
		std::atomic<std::uint32_t> m_ref_count{ 0 };
		Splines m_splines;
		float m_total_length;
	};

	PUNK_REGISTER_CREATOR(CLSID_Curve, (System::CreateInstance<Curve, ICurve>));
}
PUNK_ENGINE_END
