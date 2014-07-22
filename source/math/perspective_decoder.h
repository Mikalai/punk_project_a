#ifndef PERSPECTIVE_DECODER_H
#define PERSPECTIVE_DECODER_H

#include <cstdint>
#include <config.h>
#include "tuple.h"
#include "matrix.h"
#include "trigonometry.h"
#include "frustum_plane.h"

PUNK_ENGINE_BEGIN
namespace Math {

	template<class T>
	class PerspectiveDecoder {
	public:

		PerspectiveDecoder(const Matrix<T, 4, 4> &value)
			: m_value(value) {}

		T GetFovX() const {
			T fovx = ArcTan(1.0f / m_value[0]) * 2.0f; //  TODO: Not sure
			return fovx;
		}

		T GetFovY() const {
			T fovy = ArcTan(1.0f / m_value[5]) * 2.0f;
			return fovy;
		}

		T GetNearZ() const {
			T n = m_value[14] / (m_value[10] - 1.0f);
			return n;
		}

		T GetFarZ() const {
			T f = m_value[14] / (1.0f + m_value[10]);
			return f;
		}

		T GetWidthToHeightAspectRatio() const {
			T a = m_value[5] / m_value[0];
			return a;
		}

		const TPlane<T> GetPlane(FrustumPlane value) {
			Math::vec4 v;
			switch (value) {
			case FrustumPlane::Bottom:
				v = m_value.GetRow(3) + m_value.GetRow(1);
				break;
			case FrustumPlane::Far:
				v = m_value.GetRow(3) - m_value.GetRow(2);
				break;
			case FrustumPlane::Left:
				v = m_value.GetRow(3) + m_value.GetRow(0);
				break;
			case FrustumPlane::Near:
				v = m_value.GetRow(3) + m_value.GetRow(2);
				break;
			case FrustumPlane::Right:
				v = m_value.GetRow(3) - m_value.GetRow(0);
				break;
			case FrustumPlane::Top:
				v = m_value.GetRow(3) - m_value.GetRow(1);
				break;
			default:
				return Plane<T>();
			}
			TPlane<T> result;
			T l = Tuple<T, 3, tagVector>(v.XYZ()).Length();
			Tuple<T, 3, tagVector> n = v.XYZ() / l;
			T dst = v.W() / l;
			result.Set(n, dst);
			return result;
		}
	private:
		const Matrix<T, 4, 4>& m_value;
	};
}
PUNK_ENGINE_END

#endif // PERSPECTIVE_DECODER_H
