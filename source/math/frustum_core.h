#ifndef _H_FUSTUM_CORE
#define _H_FUSTUM_CORE

#include <config.h>
#include "vec3.h"
#include "vec2.h"
#include "mat4.h"
#include "perspective_decoder.h"
#include "clip_space.h"
#include "relations.h"
#include "trigonometry.h"

PUNK_ENGINE_BEGIN
namespace Math {

	template<class T>
	struct TFrustumCore {

		static const TFrustumCore<T> CreateFromProjectionMatrix(const Matrix<T, 4, 4> &p) {
			TFrustumCore<T> f;
			PerspectiveDecoder<T> d(p);
			f.fard = d.GetFarZ();
			f.fov = d.GetFovY();
			f.neard = d.GetNearZ();
			f.ratio = d.GetWidthToHeightAspectRatio();
			return f;
		}

		const Tuple<T, 2, tagVector> GetZRange(const Matrix<T, 4, 4>& view) const {
			// find the z-range of the current frustum as seen from the light
			// in order to increase precision
			auto transf = view * this->point[0];
			transf.Normalize();

			T min_z = transf.Z();
			T max_z = transf.Z();

			for (int j = 1; j < 8; ++j)
			{
				transf = view * this->point[j];
				transf.Normalize();
				if (transf.Z() > max_z)
					max_z = transf.Z();
				if (transf.Z() < min_z)
					min_z = transf.Z();
			}
			return{ min_z, max_z };
		}

		void Transform(
			const Tuple<T, 3, tagPoint>& center,
			const Tuple<T, 3, tagVector>&view_dir,
			const Tuple<T, 3, tagVector>&_up) {

			auto right = view_dir.Cross(_up);
			auto fc = center + view_dir*this->fard;
			auto nc = center + view_dir*this->neard;

			right = right.Normalized();
			auto up = right.Cross(view_dir);
			up = up.Normalized();

			// these heights and widths are half the heights and widths of
			// the near and far plane rectangles
			T near_height = Tan(this->fov / 2.0f) * this->neard;
			T near_width = near_height * this->ratio;
			T far_height = Tan(this->fov / 2.0f) * this->fard;
			T far_width = far_height * this->ratio;

			this->point[GetIndex(FrustumPoints::NLB)] = nc - up*near_height - right*near_width;
			this->point[GetIndex(FrustumPoints::NLT)] = nc + up*near_height - right*near_width;
			this->point[GetIndex(FrustumPoints::NRT)] = nc + up*near_height + right*near_width;
			this->point[GetIndex(FrustumPoints::NRB)] = nc - up*near_height + right*near_width;

			this->point[GetIndex(FrustumPoints::FLB)] = fc - up*far_height - right*far_width;
			this->point[GetIndex(FrustumPoints::FLT)] = fc + up*far_height - right*far_width;
			this->point[GetIndex(FrustumPoints::FRT)] = fc + up*far_height + right*far_width;
			this->point[GetIndex(FrustumPoints::FRB)] = fc - up*far_height + right*far_width;
		}

		const Matrix<T, 4, 4> ToPerspectiveProjectionMatrix() const {
			return Matrix<T, 4, 4>::CreatePerspectiveProjection(this->fov, this->ratio, 1, this->neard, this->fard);
		}

		Relation ClassifyPoint(const Tuple<T, 3, tagPoint>& point) const {
			TPlane<T> p[6];
			ProjectionMatrixToPlanes(this->ToPerspectiveProjectionMatrix(), p);
			for (int i = 0; i != 6; ++i)
			{
				if (p[i].ClassifyPoint(point) == Relation::BACK)
					return Relation::OUTSIDE;
			}
			return Relation::INSIDE;
		}

		const TClipSpace<T> ToClipSpace() const {
			TPlane<T> p[6];
			ProjectionMatrixToPlanes(this->ToPerspectiveProjectionMatrix(), p);
			ClipSpace res;
			//	skip near plane
			for (int i = 0; i != 6; ++i)
			{
				res.Add(p[i]);
			}
			return res;
		}

		const TClipSpace<T> BuildClipSpaceFromPoint(const Tuple<T, 3, tagPoint>& p) const {
			if (this->ClassifyPoint(p) == Relation::INSIDE)
				return this->ToClipSpace();

			ClipSpace result;
			//  true - point in front of the plane, false otherwise
			bool front[6];
			Math::TPlane<T> planes[6];
			ProjectionMatrixToPlanes(this->ToPerspectiveProjectionMatrix(), planes);
			for (int i = 0; i != 6; ++i) {
				front[i] = planes[i].ClassifyPoint(p) == Relation::FRONT;
				//  planes for which point is in fornt of them construct add into the resulting clipspace
				if (front[i])
					result.Add(planes[i]);
			}

			//  for each plane that forms boundary (front[i] == true) create a plane, the goes
			//  through the
			for (int i = 0; i != 6; ++i) {
				FrustumPlane plane_a = (FrustumPlane)i;
				if (!front[i])
					continue;
				const TPlane<T>& a = planes[i];
				for (int j = 0; j != 6; ++j) {
					FrustumPlane plane_b = (FrustumPlane)j;
					if (front[j] || !IsAdjacent(plane_a, plane_b))
						continue;
					const TPlane<T>& b = planes[j];
					Line<T, 3> line;
					if (a.CrossPlane(b, line) != Relation::INTERSECT)
						continue;
					TPlane<T> plane;
					plane.Set(line, p);
					result.Add(plane);
				}
			}

			return result;
		}

		T neard{ 0.1f };
		T fard{ 100.0f };
		T fov{ 1.0f };
		T ratio{ 1.33f };
		Tuple<T, 3, tagPoint>  point[8];

	private:

		void ProjectionMatrixToPlanes(const Matrix<T, 4, 4>& p, TPlane<T>(&plane)[6]) const {
			plane[GetIndex(FrustumPlane::Near)].Set(p.GetRow(3) + p.GetRow(2)).Normalize();
			plane[GetIndex(FrustumPlane::Far)].Set(p.GetRow(3) - p.GetRow(2)).Normalize();
			plane[GetIndex(FrustumPlane::Left)].Set(p.GetRow(3) + p.GetRow(0)).Normalize();
			plane[GetIndex(FrustumPlane::Right)].Set(p.GetRow(3) - p.GetRow(0)).Normalize();
			plane[GetIndex(FrustumPlane::Bottom)].Set(p.GetRow(3) + p.GetRow(1)).Normalize();
			plane[GetIndex(FrustumPlane::Top)].Set(p.GetRow(3) - p.GetRow(1)).Normalize();
			//planes2[Top].Set(0, -e * tb_coeff, -a * tb_coeff, 0);

			//        CrossThreePlane(m_planes[(int)FrustumPlane::Near], m_planes[(int)FrustumPlane::Left], m_planes[(int)FrustumPlane::Top], m_points[NLT]);
			//        CrossThreePlane(m_planes[(int)FrustumPlane::Near], m_planes[(int)FrustumPlane::Left], m_planes[(int)FrustumPlane::Bottom], m_points[NLB]);
			//        CrossThreePlane(m_planes[(int)FrustumPlane::Near], m_planes[(int)FrustumPlane::Right], m_planes[(int)FrustumPlane::Top], m_points[NRT]);
			//        CrossThreePlane(m_planes[(int)FrustumPlane::Near], m_planes[(int)FrustumPlane::Right], m_planes[(int)FrustumPlane::Bottom], m_points[NRB]);
			//        CrossThreePlane(m_planes[(int)FrustumPlane::Far], m_planes[(int)FrustumPlane::Left], m_planes[(int)FrustumPlane::Top], m_points[FLT]);
			//        CrossThreePlane(m_planes[(int)FrustumPlane::Far], m_planes[(int)FrustumPlane::Left], m_planes[(int)FrustumPlane::Bottom], m_points[FLB]);
			//        CrossThreePlane(m_planes[(int)FrustumPlane::Far], m_planes[(int)FrustumPlane::Right], m_planes[(int)FrustumPlane::Top], m_points[FRT]);
			//        CrossThreePlane(m_planes[(int)FrustumPlane::Far], m_planes[(int)FrustumPlane::Right], m_planes[(int)FrustumPlane::Bottom], m_points[FRB]);

			//        CrossThreePlane(planes2[Near], planes2[Left], planes2[Top], points2[NLT]);
			//        CrossThreePlane(planes2[Near], planes2[Left], planes2[Bottom], points2[NLB]);
			//        CrossThreePlane(planes2[Near], planes2[Right], planes2[Top], points2[NRT]);
			//        CrossThreePlane(planes2[Near], planes2[Right], planes2[Bottom], points2[NRB]);
			//        CrossThreePlane(planes2[Far], planes2[Left], planes2[Top], points2[FLT]);
			//        CrossThreePlane(planes2[Far], planes2[Left], planes2[Bottom], points2[FLB]);
			//        CrossThreePlane(planes2[Far], planes2[Right], planes2[Top], points2[FRT]);
			//        CrossThreePlane(planes2[Far], planes2[Right], planes2[Bottom], points2[FRB]);

			//		//T e = m_znear
			//T a = 1.0f / e;
			//m_planes[PLANE_NEAR].Set(vec3(0,0,-1), m_znear);
			//m_planes[PLANE_FAR].Set(vec3(0,0,1), m_zfar);
			//m_planes[PLANE_LEFT].Set(vec3(e/sqrt(e*e+1), 0, -1/sqrt(e*e+1)), 0);
			//m_planes[PLANE_RIGHT].Set(vec3(-e/sqrt(e*e+1), 0, -1/sqrt(e*e+1)), 0);
			//m_planes[PLANE_BOTTOM].Set(vec3(0, e/sqrt(e*e+a*a), -1/sqrt(e*e+a*a)), 0);
			//m_planes[PLANE_TOP].Set(vec3(0, -e/sqrt(e*e+a*a), -1/sqrt(e*e+a*a)), 0);
		}
	};

	using FrustumCore = TFrustumCore < float > ;
}

PUNK_ENGINE_END

#endif	//	_H_FUSTUM_CORE
