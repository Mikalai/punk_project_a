#ifndef _H_PUNK_MATH_SHAPE_MESH
#define _H_PUNK_MATH_SHAPE_MESH

#include <cstdint>
#include <config.h>
#include "tuple.h"
#include "line.h"
#include "triangle.h"
#include "bounding_box.h"
#include "bounding_sphere.h"

PUNK_ENGINE_BEGIN
namespace Math {

    template<class T>
    class ConvexShapeMeshTemplate {
    public:

        void SetPoints(const std::vector<Tuple<T, 3, tagPoint>>& points) {
            SetPoints(points.data(), (std::uint32_t)points.size());
        }

        void SetPoints(const Tuple<T, 3, tagPoint>* points, std::uint32_t count) {
            m_points.resize(count);
            for (auto i = 0u; i < count; ++i) {
                m_points[i] = points[i];
            }
            UpdateBoundingVolumes();
        }

        void SetFaces(const std::vector<Tuple<std::uint32_t, 3, tagIndex>>& faces) {
            SetFaces(faces.data(), (std::uint32_t)faces.size());
        }

        void SetFaces(const Tuple<std::uint32_t, 3, tagIndex>* faces, std::uint32_t count) {
            m_faces.resize(count);
            for (auto i = 0u; i < count; ++i) {
                m_faces[i] = faces[i];
            }
        }

        void SetNormals(const std::vector<Tuple<T, 3, tagVector>>& normals) {
            SetNormals(normals.data(), (std::uint32_t)normals.size());
        }

        void SetNormals(const Tuple<T, 3, tagVector>* normals, std::uint32_t count) {
            m_normals.resize(count);
            for (auto i = 0u; i < count; ++i) {
                m_normals[i] = normals[i];
            }
        }

        const Tuple<T, 3, tagPoint>& GetPoint(std::uint32_t index) const {
            return m_points[index];
        }

        const Tuple<std::uint32_t, 3, tagIndex>& GetFace(std::uint32_t index) const {
            return m_faces[index];
        }

        const Tuple<T, 3, tagVector>& GetNormal(std::uint32_t index) const {
            return m_normals[index];
        }

        const TBoundingBox<T>& GetBoundingBox() const {
            return m_bbox;
        }

        const TBoundingSphere<T>& GetBoundingSphere() const {
            return m_bsphere;
        }

        std::uint32_t GetFaceCount() const {
            return (std::uint32_t)m_faces.size();
        }

        std::uint32_t GetPointsCount() const {
            return (std::uint32_t)m_points.size();
        }

        std::uint32_t GetNormalsCount() const {
            return (std::uint32_t)m_normals.size();
        }

		Relation ClassifyPoint(const vec3& point)
		{
			Relation relation = ClassifyPoint(point, this->GetBoundingSphere());
			if (relation == Relation::OUTSIDE)
				return Relation::OUTSIDE;

			relation = ClassifyPoint(point, this->GetBoundingBox());
			if (relation == Relation::OUTSIDE)
				return Relation::OUTSIDE;

			for (int i = 0; i < (int)this->GetFaceCount(); ++i)
			{
				auto face = this->GetFace(i);
				TPlane<T> p(this->GetPoint(face[0]), this->GetNormal(i));
				Relation relation = ClassifyPoint(point, p);
				if (relation == Relation::BACK)
					return Relation::OUTSIDE;
			}
			return Relation::INSIDE;
		}

		Relation CrossLine(
			const Line3D &line, 
			std::vector<Tuple<T, 3, tagPoint>>& res_points, 
			std::vector<Tuple<T, 3, tagIndex>>& res_faces)
		{
			res_faces.clear();
			res_points.clear();
			for (std::size_t i = 0; i != this->m_faces.size(); ++i)
			{
				const auto& face = this->m_faces[i];
				const auto& p0 = this->m_point[face[0]];
				const auto& p1 = this->m_point[face[1]];
				const auto& p2 = this->m_point[face[2]];

				const Triangle<T, 3> triangle{ p0, p1, p2 };
				T t;
				Relation res = triangle.CrossLine(line, t);

				if (res == Relation::INTERSECT)
				{
					res_points.push_back(line.PointAt(t));
					res_faces.push_back(i);
				}
			}
			if (res_faces.empty())
				return Relation::NOT_INTERSECT;

			return Relation::INTERSECT;
		}

    private:
        typedef std::vector<Tuple<T, 3, tagPoint>> PointsCollection;
        typedef std::vector<Tuple<std::uint32_t, 3, tagIndex>> FacesCollection;
        typedef std::vector<Tuple<T, 3, tagVector>> NormalsCollection;
        TBoundingBox<T> m_bbox;
        TBoundingSphere<T> m_bsphere;

        PointsCollection m_points;
        FacesCollection m_faces;
        NormalsCollection m_normals;

        void UpdateBoundingVolumes() {
            m_bbox.Create(m_points);
            m_bsphere.Create(m_points);
        }
    };

    using ConvexShapeMesh = ConvexShapeMeshTemplate<float>;
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_MATH_SHAPE_MESH
