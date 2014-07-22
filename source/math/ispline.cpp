#include <cstdint>
#include <system/factory/module.h>
#include <vector>
#include "ispline.h"
#include "weighted_point.h"

PUNK_ENGINE_BEGIN
namespace Math
{
	class PUNK_ENGINE_LOCAL Spline : public ISpline
	{
	public:
		Spline();
		virtual ~Spline();

		//	IObject
		void QueryInterface(const Core::Guid& type, void** object) override;
		std::uint32_t AddRef() override;
		std::uint32_t Release() override;

		//	ISpline
		void AddPoint(const WeightedPoint& value) override;
		void AddPoints(const std::vector<WeightedPoint>& value) override;
		float GetTotalLength() const override;
		const WeightedPoint At(float t) override;
		std::uint32_t GetPointsCount() const override;
		const WeightedPoint& GetPoint(int index) const override;

	private:
		void UpdateTotalLength();
	private:
		std::atomic<std::uint32_t> m_ref_count{ 0 };
		std::vector<WeightedPoint> m_points;
		float m_total_length;
	};

	void Spline::QueryInterface(const Core::Guid& type, void** object) {
		Core::QueryInterface(this, type, object, { Core::IID_IObject, IID_ISpline });
	}

	std::uint32_t Spline::AddRef() {
		return m_ref_count.fetch_add(1);
	}

	std::uint32_t Spline::Release() {
		auto v = m_ref_count.fetch_sub(1) - 1;
		if (!v) {
			delete this;
		}
		return v;
	}

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

	PUNK_REGISTER_CREATOR(IID_ISpline, (System::CreateInstance<Spline, ISpline>));
}
PUNK_ENGINE_END
