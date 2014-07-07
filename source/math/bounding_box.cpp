#include <ostream>
#include <istream>

#include "vec3.h"
#include "mat3.h"
#include "mat4.h"
#include "plane.h"
#include "bounding_box.h"
#include "bounding_sphere.h"
#include "mat3.h"
#include "math_error.h"
#include "volume_construction.h"

PUNK_ENGINE_BEGIN
namespace Math {

	BoundingBox::BoundingBox()
	{}

	BoundingBox::BoundingBox(const BoundingBox& value)
		: m_core(value.m_core) {}

	BoundingBox& BoundingBox::operator = (const BoundingBox& value) {
		if (this != &value) {
			m_core = value.m_core;
		}
		return *this;
	}

	void BoundingBox::Create(const vec3* points, std::uint32_t count)
	{
		//	check input data
		if (!points || count == 0)
			throw Error::NotEnoughData(0);

		//	find average of the vertices
		m_core.m_center_of_mass = CalculateAverage(points, count);

		CalculateNativeAxis(points, count, m_core.m_r, m_core.m_s, m_core.m_t);

		//	find plane distances
		float d[6];

		//	init distances with appropriate values
		const vec3 v = points[0];
		d[0] = v.Dot(m_core.m_r);
		d[1] = v.Dot(m_core.m_r);

		d[2] = v.Dot(m_core.m_s);
		d[3] = v.Dot(m_core.m_s);

		d[4] = v.Dot(m_core.m_t);
		d[5] = v.Dot(m_core.m_t);

		for (auto i = 0u; i < count; ++i)
		{
			float r = m_core.m_r.Dot(v);
			if (d[0] > r)
				d[0] = r;
			if (d[1] < r)
				d[1] = r;

			float s = m_core.m_s.Dot(v);
			if (d[2] > s)
				d[2] = s;
			if (d[3] < s)
				d[3] = s;

			float t = m_core.m_t.Dot(v);
			if (d[4] > t)
				d[4] = t;
			if (d[5] < t)
				d[5] = t;
		}

		//	find natural planes
		m_core.m_plane[0].Set(m_core.m_r, -d[0]);
		m_core.m_plane[1].Set(-m_core.m_r, d[1]);
		m_core.m_plane[2].Set(m_core.m_s, -d[2]);
		m_core.m_plane[3].Set(-m_core.m_s, d[3]);
		m_core.m_plane[4].Set(m_core.m_t, -d[4]);
		m_core.m_plane[5].Set(-m_core.m_t, d[5]);

		//	find bbox center
		{
			float a = (d[0] + d[1]) / 2.0f;
			float b = (d[2] + d[3]) / 2.0f;
			float c = (d[4] + d[5]) / 2.0f;

			m_core.m_center = a*m_core.m_r + b*m_core.m_s + c*m_core.m_t;

			m_core.m_r *= (d[1] - d[0]);
			m_core.m_s *= (d[3] - d[2]);
			m_core.m_t *= (d[5] - d[4]);

			m_core.m_min_corner = m_core.m_center - m_core.m_r * 0.5f - m_core.m_s * 0.5f - m_core.m_t * 0.5f;
		}
	}

	const BoundingSphere BoundingBox::ToBoundingSphere()
	{
		vec3 p[] {m_core.m_min_corner, m_core.m_min_corner + m_core.m_r + m_core.m_s + m_core.m_t, m_core.m_min_corner + m_core.m_r, m_core.m_min_corner + m_core.m_s};
		BoundingSphere s;
		s.Create(p, sizeof(p) / sizeof(p[0]));
		return s;
	}

	const BoundingBox operator * (const mat4& m, const BoundingBox& bbox)
	{
		BoundingBox res;
		mat4 plane_matrix = m.Inversed().Transposed();
		mat3 normal_matrix = plane_matrix.RotationPart();

		res.m_core.m_center_of_mass = m * bbox.m_core.m_center_of_mass;
		res.m_core.m_center = m * bbox.m_core.m_center;
		res.m_core.m_r = normal_matrix * bbox.m_core.m_r;
		res.m_core.m_s = normal_matrix * bbox.m_core.m_s;
		res.m_core.m_t = normal_matrix * bbox.m_core.m_t;

		for (int i = 0; i < 6; ++i)
		{
			res.m_core.m_plane[i] = plane_matrix * bbox.m_core.m_plane[i];
		}

		return res;
	}

	const vec3& BoundingBox::GetR() const {
		return m_core.m_r;
	}

	const vec3& BoundingBox::GetS() const {
		return m_core.m_s;
	}

	const vec3& BoundingBox::GetT() const {
		return m_core.m_t;
	}

	const vec3& BoundingBox::GetCenter() const {
		return m_core.m_center;
	}

	const vec3& BoundingBox::GetMassCenter() const {
		return m_core.m_center_of_mass;
	}

	const vec3& BoundingBox::GetMinCorner() const {
		return m_core.m_min_corner;
	}

	const Plane& BoundingBox::GetPlane(int index) const {
		return m_core.m_plane[index];
	}

	//    void SaveBoundingBox(Core::Buffer *buffer, const BoundingBox& value)
	//    {
	//        SaveVector3f(buffer, value.m_center_of_mass);
	//        SaveVector3f(buffer, value.m_center);
	//        SaveVector3f(buffer, value.m_r);
	//        SaveVector3f(buffer, value.m_s);
	//        SaveVector3f(buffer, value.m_t);
	//        for (int i = 0; i < 6; ++i)
	//            SavePlane(buffer, value.m_plane[i]);
	//    }

	//    void LoadBoundingBox(Core::Buffer *buffer, BoundingBox& value)
	//    {
	//        LoadVector3f(buffer, value.m_center_of_mass);
	//        LoadVector3f(buffer, value.m_center);
	//        LoadVector3f(buffer, value.m_r);
	//        LoadVector3f(buffer, value.m_s);
	//        LoadVector3f(buffer, value.m_t);
	//        for (int i = 0; i < 6; ++i)
	//            LoadPlane(buffer, value.m_plane[i]);
	//    }
}
PUNK_ENGINE_END