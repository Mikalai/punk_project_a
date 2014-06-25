#include <system/factory/module.h>
#include "spline.h"
#include <cstdint>

PUNK_ENGINE_BEGIN
namespace Math
{
    Spline::Spline()
        : m_total_length(0)
    {
    }

	Spline::~Spline() {}

    void Spline::AddPoint(const WeightedPoint &value)
    {
        m_points.push_back(value);
        UpdateTotalLength();
    }

    void Spline::AddPoints(const std::vector<WeightedPoint> &value)
    {
        m_points.insert(std::end(m_points), value.begin(), value.end());
        UpdateTotalLength();
    }

    float Spline::GetTotalLength() const
    {
        return m_total_length;
    }

    void Spline::UpdateTotalLength()
    {
        m_total_length = 0;
        for (std::size_t i = 0, max_i = m_points.size()-1; i != max_i; ++i)
        {
            const auto& p0 = m_points[i];
            const auto& p1 = m_points[i+1];
            m_total_length += (p1 - p0).Length();
        }
    }

    const WeightedPoint Spline::At(float t)
    {
        if (m_points.empty())
            return WeightedPoint();
        if (t <= 0.0f)
            return m_points.front();
        if (t >= 1.0f)
            return m_points.back();
        float req_length = m_total_length * t;
        float cur_length = 0;
        std::size_t index = 0;
        while (cur_length < req_length && index != m_points.size() - 1)
        {
            const auto& p0 = m_points[index];
            const auto& p1 = m_points[index+1];
            cur_length += (p1 - p0).Length();
            index++;
        }
        float x = (cur_length  - req_length) / (m_points[index].GetPoint() - m_points[index-1].GetPoint()).Length();
        auto res = m_points[index - 1] * x + m_points[index] * (1.0f - x);
        return res;
    }

    std::uint32_t Spline::GetPointsCount() const {
        return (std::uint32_t)m_points.size();
    }

    const WeightedPoint& Spline::GetPoint(int index) const {
        return m_points.at(index);
    }

	void Spline::QueryInterface(const Core::Guid& type, void** object) {
		if (!object)
			return;

		if (type == Core::IID_IObject ||
			type == IID_ISpline) {
			*object = (void*)this;
			AddRef();
		}
		else
			*object = nullptr;
	}

	void CreateSpline(void** object) {
		if (!object)
			return;
		*object = (void*)(new Spline);
	}

	PUNK_REGISTER_CREATOR(IID_ISpline, CreateSpline);
}
PUNK_ENGINE_END
