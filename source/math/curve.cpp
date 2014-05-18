#include <core/ifactory.h>
#include <cstdint>
#include "vec3.h"
#include "curve.h"

PUNK_ENGINE_BEGIN
namespace Math
{
	Curve::Curve() {}

	Curve::~Curve() {
		while (!m_splines.empty()) {
			m_splines.back()->Release();
			m_splines.pop_back();
		}
	}
	void Curve::AddSpline(ISpline* value) {
		m_total_length = 0;
		m_splines.push_back(value);
		for (ISpline* s : m_splines) {
			m_total_length += s->GetTotalLength();
		}
	}

	void Curve::AddSplines(const std::vector<ISpline*>& value) {
		m_splines.insert(m_splines.end(), value.begin(), value.end());
		m_total_length = 0;
		for (ISpline* s : m_splines) {
			m_total_length += s->GetTotalLength();
		}
	}

	std::uint32_t Curve::GetSplinesCount() const {
		return (std::uint32_t)m_splines.size();
	}

	const ISpline* Curve::GetSpline(std::uint32_t index) const {
		return m_splines[index];
	}

	const Math::vec3 Curve::At(float t) {
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
			return Math::vec3();

		float tt = (t - prev_t) / (cur_t - prev_t);
		WeightedPoint p = m_splines[spline_index]->At(tt);
		return p.GetPoint().XYZ();
	}

	float Curve::GetTotalLength() const {
		return m_total_length;
	}

	void Curve::Clear() {
		m_total_length = 0;
		m_splines.clear();
	}

	void Curve::QueryInterface(const Core::Guid& type, void** object) {
		if (!object)
			return;
		if (type == Core::IID_IObject ||
			type == IID_ICurve){
			*object = (void*)this;
			AddRef();
		}
		else
			*object = nullptr;
	}

	void CreateCurve(void** object) {
		if (!object)
			return;
		*object = (void*)(new Curve);
	}

	PUNK_REGISTER_CREATOR(IID_ICurve, CreateCurve);

}
PUNK_ENGINE_END