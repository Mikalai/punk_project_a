#ifndef _H_MATH_TUPLE
#define _H_MATH_TUPLE

#ifdef USE_QT
#include <QPointF>
#endif  //  USE_QT

#include <initializer_list>
#include <array>
#include <vector>
#include <cstdint>
#include <config.h>
#include <algorithm>
#include "constants.h"
#include "square_root.h"
#include "absolute_value.h"
#include "forward.h"

#ifdef USE_QT
#include <QString>
#include <QStringList>
#else
#include <string/string.h>
#include <string/string_list.h>
#endif

PUNK_ENGINE_BEGIN
namespace Math {

	struct tagPoint;
	struct tagColor;
	struct tagVector;
	struct tagQuaternion;
	struct tagIndex;

	template<class T, int D, typename tag> class Tuple;

	template<typename T, int D, typename tag>
	struct TupleData {
	public:
		TupleData() {
			std::fill(m_v.begin(), m_v.end(), T{ 0 });
		}

		TupleData(const TupleData<T, D, tag>& value) {
			std::copy(value.m_v.begin(), value.m_v.end(), m_v.begin());
		}

		TupleData(const T& value) {
			std::fill(m_v.begin(), m_v.end(), value);
		}

		TupleData(std::initializer_list<T> list) {
			std::copy_n(list.begin(), D, m_v.begin());
		}

		TupleData(const TupleData<T, D, tag>& origin, const TupleData<T, D, tag>& destination) {
			for (auto i = 0; i < D; ++i) {
				m_v[i] = destination.m_v[i] - origin.m_v[i];
			}
		}

		TupleData<T, D, tag>& operator = (const TupleData<T, D, tag>& value) {
			if (this == &value)
				return *this;
			std::copy(value.m_v.begin(), value.m_v.end(), m_v.begin());
			return *this;
		}

		bool IsEqual(const TupleData<T, D, tag>& v, const T eps = Eps) const {
			for (auto i = 0; i < D; ++i)
				if (Abs(m_v[i] - v.m_v[i]) > eps)
					return false;
			return true;
		}

		std::array<T, D> m_v;
	};

	template<typename T, int D, typename tag>
	struct TupleComponentAccessorBase : public TupleData < T, D, tag > {

		using TupleData<T, D, tag>::TupleData;

		TupleComponentAccessorBase() {}

		TupleComponentAccessorBase(const TupleData<T, D, tag>& value)
			: TupleData<T, D, tag>(value) {}

		T& operator[] (std::uint32_t index) {
			return this->m_v[index];
		}

		const T& operator[] (std::uint32_t index) const {
			return this->m_v[index];
		}

		T& at(std::uint32_t index) {
			return this->m_v.at(index);
		}

		const T& at(std::uint32_t index) const {
			return this->m_v.at(index);
		}

		operator T* () {
			return this->m_v.data();
		}

		operator const T* () const {
			return this->m_v.data();
		}
#ifdef USE_QT
        const QPointF ToQPointF() const {
            return QPointF{this->m_v[0], this->m_v[1]};
        }

        TupleComponentAccessorBase(const QPointF& p) {
            this->m_v[0] = p.x();
            this->m_v[1] = p.y();
        }

#endif // USE_QT
	};


	template<typename T, int D, typename tag>
	struct TupleComponentAccessor : public TupleComponentAccessorBase < T, D, tag > {
		using TupleComponentAccessorBase<T, D, tag>::TupleComponentAccessorBase;

		TupleComponentAccessor() {}
		TupleComponentAccessor(const TupleData<T, D, tag>& value)
			: TupleComponentAccessorBase<T, D, tag>(value) {}
	};

	template<typename T, typename tag>
	struct TupleComponentAccessor<T, 2, tag> : public TupleComponentAccessorBase < T, 2, tag > {

		using Base = TupleComponentAccessorBase < T, 2, tag > ;
		using TupleComponentAccessorBase<T, 2, tag>::TupleComponentAccessorBase;

		TupleComponentAccessor() {}
		TupleComponentAccessor(const TupleData<T, 2, tag>& value)
			: TupleComponentAccessorBase<T, 2, tag>(value) {}

		TupleComponentAccessor(const T& x, const T& y)
			: TupleComponentAccessor({ x, y }){}

		TupleData<T, 2, tag>& Set(const T& x, const T& y) {
			this->m_v[0] = x; this->m_v[1] = y;
			return *this;
		}

		const T& X() const {
			return this->m_v[0];
		}

		T& X() {
			return this->m_v[0];
		}

		T& Y() {
			return this->m_v[1];
		}

		const T& Y() const {
			return this->m_v[1];
		}

		const TupleData<T, 2, tag> XY() const {
			return TupleData < T, 2, tag > { { this->m_v[0], this->m_v[1] } };
		}

		const TupleData<T, 2, tag> YX() const {
			return TupleData < T, 2, tag > { { this->m_v[1], this->m_v[0] } };
		}
	};

	template<typename T, typename tag>
	struct TupleComponentAccessor<T, 3, tag> : public TupleComponentAccessorBase < T, 3, tag > {

		using BaseType = TupleComponentAccessor < T, 2, tag > ;
		using Type = TupleComponentAccessor < T, 3, tag > ;

		using TupleComponentAccessorBase<T, 3, tag>::TupleComponentAccessorBase;

		TupleComponentAccessor() {}

		TupleComponentAccessor(const TupleData<T, 3, tag>& value)
			: TupleComponentAccessor{ { value.m_v[0], value.m_v[1], value.m_v[2] } } {}

		TupleComponentAccessor(const TupleData<T, 2, tag>& value)
			: TupleComponentAccessor{ { value.m_v[0], value.m_v[1], T{ 0 } } } {}

		TupleComponentAccessor(const T& x, const T& y, const T& z) {
			this->m_v[0] = x; this->m_v[1] = y; this->m_v[2] = z;
		}

		void Set(const T& x, const T& y, const T& z) {
			this->m_v[0] = x; this->m_v[1] = y; this->m_v[2] = z;
		}

		const T& X() const {
			return this->m_v[0];
		}

		T& X() {
			return this->m_v[0];
		}

		T& Y() {
			return this->m_v[1];
		}

		const T& Y() const {
			return this->m_v[1];
		}

		const TupleData<T, 2, tag> XY() const {
			return TupleData < T, 2, tag > { { this->m_v[0], this->m_v[1] } };
		}

		const TupleData<T, 2, tag> YX() const {
			return TupleData < T, 2, tag > { { this->m_v[1], this->m_v[0] } };
		}

		const T& Z() const {
			return this->m_v[2];
		}

		T& Z() {
			return this->m_v[2];
		}

		const Tuple<T, 2, tag> XZ() const {
			return TupleData < T, 2, tag > { this->m_v[0], this->m_v[2] };
		}

		const Tuple<T, 2, tag> ZX() const {
			return TupleData < T, 2, tag > {{ this->m_v[2], this->m_v[0] }};
		}

		const Tuple<T, 2, tag> YZ() const {
			return TupleData < T, 2, tag > {{ this->m_v[1], this->m_v[2] }};
		}

		const Tuple<T, 2, tag> ZY() const {
			return TupleData < T, 2, tag > {{ this->m_v[2], this->m_v[1] }};
		}

		const Tuple<T, 3, tag>  XYZ() const {
			return TupleData < T, 3, tag > {{ this->m_v[0], this->m_v[1], this->m_v[2] }};
		}

		const Tuple<T, 3, tag> XZY() const {
			return TupleData < T, 3, tag > {{ this->m_v[0], this->m_v[2], this->m_v[1] }};
		}

		const Tuple<T, 3, tag> YXZ() const {
			return TupleData < T, 3, tag > {{ this->m_v[1], this->m_v[0], this->m_v[2] }};
		}

		const Tuple<T, 3, tag> YZX() const {
			return TupleData < T, 3, tag > {{ this->m_v[1], this->m_v[2], this->m_v[0] }};
		}

		const Tuple<T, 3, tag> ZXY() const {
			return TupleData < T, 3, tag > {{ this->m_v[2], this->m_v[0], this->m_v[1] }};
		}

		const Tuple<T, 3, tag> ZYX() const {
			return TupleData < T, 3, tag > {{ this->m_v[2], this->m_v[1], this->m_v[0] }};
		}
	};

	template<typename T, typename tag>
	struct TupleComponentAccessor<T, 4, tag> : public TupleComponentAccessorBase < T, 4, tag > {

		using BaseType = TupleComponentAccessor < T, 3, tag > ;
		using Type = TupleComponentAccessor < T, 4, tag > ;

		using TupleComponentAccessorBase<T, 4, tag>::TupleComponentAccessorBase;

		TupleComponentAccessor() {}

		TupleComponentAccessor(const TupleData<T, 3, tag>& v, const T& value)
            : TupleComponentAccessorBase<T, 4, tag>{ { v.m_v[0], v.m_v[1], v.m_v[2], value } } {}

		TupleComponentAccessor(const TupleData<T, 3, tag>& value)
			: TupleComponentAccessor{ { value.m_v[0], value.m_v[1], value.m_v[2] } } {}

		TupleComponentAccessor(const TupleData<T, 2, tag>& value)
			: TupleComponentAccessor{ { value.m_v[0], value.m_v[1], T{ 0 }, T{ 1 } } } {}

		TupleComponentAccessor(const T& x, const T& y, const T& z, const T& w)
			: TupleComponentAccessor({ x, y, z, w }) {}

		TupleData<T, 4, tag>& Set(const T& x, const T& y, const T& z, const T& w) {
			this->m_v[0] = x; this->m_v[1] = y; this->m_v[2] = z; this->m_v[3] = w;
			return *this;
		}

		const T& X() const {
			return this->m_v[0];
		}

		T& X() {
			return this->m_v[0];
		}

		T& Y() {
			return this->m_v[1];
		}

		const T& Y() const {
			return this->m_v[1];
		}

		const Tuple<T, 2, tag> XY() const {
			return TupleData < T, 2, tag > { { this->m_v[0], this->m_v[1] } };
		}

		const Tuple<T, 2, tag> YX() const {
			return TupleData < T, 2, tag > { { this->m_v[1], this->m_v[0] } };
		}

		const T& Z() const {
			return this->m_v[2];
		}

		T& Z() {
			return this->m_v[2];
		}

		const Tuple<T, 2, tag> XZ() const {
			return TupleData < T, 2, tag > { this->m_v[0], this->m_v[2] };
		}

		const Tuple<T, 2, tag> ZX() const {
			return TupleData < T, 2, tag > {{ this->m_v[2], this->m_v[0] }};
		}

		const Tuple<T, 2, tag> YZ() const {
			return TupleData < T, 2, tag > {{ this->m_v[1], this->m_v[2] }};
		}

		const Tuple<T, 2, tag> ZY() const {
			return TupleData < T, 2, tag > {{ this->m_v[2], this->m_v[1] }};
		}

		const Tuple<T, 3, tag>  XYZ() const {
			return TupleData < T, 3, tag > {{ this->m_v[0], this->m_v[1], this->m_v[2] }};
		}

		const Tuple<T, 3, tag> XZY() const {
			return TupleData < T, 3, tag > {{ this->m_v[0], this->m_v[2], this->m_v[1] }};
		}

		const Tuple<T, 3, tag> YXZ() const {
			return TupleData < T, 3, tag > {{ this->m_v[1], this->m_v[0], this->m_v[2] }};
		}

		const Tuple<T, 3, tag> YZX() const {
			return TupleData < T, 3, tag > {{ this->m_v[1], this->m_v[2], this->m_v[0] }};
		}

		const Tuple<T, 3, tag> ZXY() const {
			return TupleData < T, 3, tag > {{ this->m_v[2], this->m_v[0], this->m_v[1] }};
		}

		const Tuple<T, 3, tag> ZYX() const {
			return TupleData < T, 3, tag > {{ this->m_v[2], this->m_v[1], this->m_v[0] }};
		}

		const T& W() const {
			return this->m_v[3];
		}

		T& W() {
			return this->m_v[3];
		}

		const Tuple<T, 2, tag> XW() const {
			return TupleData < T, 2, tag > {{this->m_v[0], this->m_v[3]}};
		}

		const Tuple<T, 2, tag> WX() const {
			return TupleData < T, 2, tag > {{this->m_v[3], this->m_v[0]}};
		}

		const Tuple<T, 2, tag> WZ() const {
			return TupleData < T, 2, tag > {{this->m_v[3], this->m_v[2]}};
		}

		const Tuple<T, 2, tag> ZW() const {
			return TupleData < T, 2, tag > {{this->m_v[2], this->m_v[3]}};
		}

		const Tuple<T, 2, tag> YW() const {
			return TupleData < T, 2, tag > {{this->m_v[1], this->m_v[3]}};
		}

		const Tuple<T, 2, tag> WY() const {
			return TupleData < T, 2, tag > {{this->m_v[3], this->m_v[1]}};
		}

		const Tuple<T, 3, tag> XYW() const {
			return TupleData < T, 3, tag > {{this->X(), this->Y(), this->W()}};
		}

		const Tuple<T, 3, tag> XZW() const {
			return TupleData < T, 3, tag > {{this->X(), this->Z(), this->W()}};
		}

		const Tuple<T, 3, tag> XWZ() const {
			return TupleData < T, 3, tag > {{this->X(), this->W(), this->Z()}};
		}

		const Tuple<T, 3, tag> XWY() const {
			return TupleData < T, 3, tag > {{this->X(), this->W(), this->Y()}};
		}

		const Tuple<T, 3, tag> YXW() const {
			return TupleData < T, 3, tag > {{this->Y(), this->X(), this->W()}};
		}

		const Tuple<T, 3, tag> YZW() const {
			return TupleData < T, 3, tag > {{this->Y(), this->Z(), this->W()}};
		}

		const Tuple<T, 3, tag> YWX() const {
			return TupleData < T, 3, tag > {{this->Y(), this->W(), this->X()}};
		}

		const Tuple<T, 3, tag> YWZ() const {
			return TupleData < T, 3, tag > {{this->Y(), this->W(), this->Z()}};
		}

		const Tuple<T, 3, tag> ZXW() const {
			return TupleData < T, 3, tag > {{this->Z(), this->X(), this->W()}};
		}

		const Tuple<T, 3, tag> ZYW() const {
			return TupleData < T, 3, tag > {{this->Z(), this->Y(), this->W()}};
		}

		const Tuple<T, 3, tag> ZWX() const {
			return TupleData < T, 3, tag > {{this->Z(), this->W(), this->X()}};
		}

		const Tuple<T, 3, tag> ZWY() const {
			return TupleData < T, 3, tag > {{this->Z(), this->W(), this->Y()}};
		}

		const Tuple<T, 3, tag> WXY() const {
			return TupleData < T, 3, tag > {{this->W(), this->X(), this->Y()}};
		}

		const Tuple<T, 3, tag> WXZ() const {
			return TupleData < T, 3, tag > {{this->W(), this->X(), this->Z()}};
		}

		const Tuple<T, 3, tag> WYX() const {
			return TupleData < T, 3, tag > {{this->W(), this->Y(), this->X()}};
		}

		const Tuple<T, 3, tag> WYZ() const {
			return TupleData < T, 3, tag > {{this->W(), this->Y(), this->Z()}};
		}

		const Tuple<T, 3, tag> WZX() const {
			return TupleData < T, 3, tag > {{this->W(), this->Z(), this->X()}};
		}

		const Tuple<T, 3, tag> WZY() const {
			return TupleData < T, 3, tag > {{this->W(), this->Z(), this->Y()}};
		}

		const Tuple<T, 4, tag> XYZW() const {
			return TupleData < T, 4, tag > {{this->m_v[0], this->m_v[1], this->m_v[2], this->m_v[3]}};
		}

		const Tuple<T, 4, tag> XYWZ() const {
			return TupleData < T, 4, tag > {{this->m_v[0], this->m_v[1], this->m_v[3], this->m_v[2]}};
		}

		const Tuple<T, 4, tag> XZYW() const {
			return TupleData < T, 4, tag > {{ this->m_v[0], this->m_v[2], this->m_v[1], this->m_v[3] }};
		}

		const Tuple<T, 4, tag> XZWY() const {
			return TupleData < T, 4, tag > {{this->m_v[0], this->m_v[2], this->m_v[3], this->m_v[1]}};
		}

		const Tuple<T, 4, tag> XWYZ() const {
			return TupleData < T, 4, tag > {{this->m_v[0], this->m_v[3], this->m_v[1], this->m_v[2]}};
		}

		const Tuple<T, 4, tag> XWZY() const {
			return TupleData < T, 4, tag > {{this->m_v[0], this->m_v[3], this->m_v[2], this->m_v[1]}};
		}

		const Tuple<T, 4, tag> YXZW() const {
			return TupleData < T, 4, tag > {{this->m_v[1], this->m_v[0], this->m_v[2], this->m_v[3]}};
		}

		const Tuple<T, 4, tag> YXWZ() const {
			return TupleData < T, 4, tag > {{this->m_v[1], this->m_v[0], this->m_v[3], this->m_v[2]}};
		}

		const Tuple<T, 4, tag> YZXW() const {
			return TupleData < T, 4, tag > {{this->m_v[1], this->m_v[2], this->m_v[0], this->m_v[3]}};
		}

		const Tuple<T, 4, tag> YZWX() const {
			return TupleData < T, 4, tag > {{this->m_v[1], this->m_v[2], this->m_v[3], this->m_v[0]}};
		}

		const Tuple<T, 4, tag> YWZX() const {
			return TupleData < T, 4, tag > {{this->m_v[1], this->m_v[3], this->m_v[2], this->m_v[0]}};
		}

		const Tuple<T, 4, tag> YWXZ() const {
			return TupleData < T, 4, tag > {{this->m_v[1], this->m_v[3], this->m_v[0], this->m_v[2]}};
		}


		const Tuple<T, 4, tag> ZXYW() const {
			return TupleData < T, 4, tag > {{this->m_v[2], this->m_v[0], this->m_v[1], this->m_v[3]}};
		}

		const Tuple<T, 4, tag> ZXWY() const {
			return TupleData < T, 4, tag > {{this->m_v[2], this->m_v[0], this->m_v[3], this->m_v[1]}};
		}

		const Tuple<T, 4, tag> ZYXW() const {
			return TupleData < T, 4, tag > {{this->m_v[2], this->m_v[1], this->m_v[0], this->m_v[3]}};
		}

		const Tuple<T, 4, tag> ZYWX() const {
			return TupleData < T, 4, tag > {{this->m_v[2], this->m_v[1], this->m_v[3], this->m_v[0]}};
		}

		const Tuple<T, 4, tag> ZWXY() const {
			return TupleData < T, 4, tag > {{this->m_v[2], this->m_v[3], this->m_v[0], this->m_v[1]}};
		}

		const Tuple<T, 4, tag> ZWYX() const {
			return TupleData < T, 4, tag > {{this->m_v[2], this->m_v[3], this->m_v[1], this->m_v[0]}};
		}

		const Tuple<T, 4, tag> WXYZ() const {
			return TupleData < T, 4, tag > {{this->m_v[3], this->m_v[0], this->m_v[1], this->m_v[2]}};
		}

		const Tuple<T, 4, tag> WXZY() const {
			return TupleData < T, 4, tag > {{this->m_v[3], this->m_v[0], this->m_v[2], this->m_v[1]}};
		}

		const Tuple<T, 4, tag> WYXZ() const {
			return TupleData < T, 4, tag > {{this->m_v[3], this->m_v[1], this->m_v[0], this->m_v[2]}};
		}

		const Tuple<T, 4, tag> WYZX() const {
			return TupleData < T, 4, tag > {{this->m_v[3], this->m_v[1], this->m_v[2], this->m_v[0]}};
		}

		const Tuple<T, 4, tag> WZXY() const {
			return TupleData < T, 4, tag > {{this->m_v[3], this->m_v[2], this->m_v[0], this->m_v[1]}};
		}

		const Tuple<T, 4, tag> WZYX() const {
			return TupleData < T, 4, tag > {{this->m_v[3], this->m_v[2], this->m_v[1], this->m_v[0]}};
		}
	};

	template<typename T>
	struct TupleComponentAccessor<T, 4, tagQuaternion> : public TupleComponentAccessorBase < T, 4, tagQuaternion > {

		using Base = TupleComponentAccessorBase < T, 4, tagQuaternion > ;
		using TupleComponentAccessorBase<T, 4, tagQuaternion >::TupleComponentAccessorBase;

		TupleComponentAccessor()
			: TupleComponentAccessor{ { T{ 1 }, T{ 0 }, T{ 0 }, T{ 0 } } } {}

		TupleComponentAccessor(const TupleData<T, 4, tagQuaternion >& value)
			: TupleComponentAccessorBase<T, 4, tagQuaternion >(value) {}

		TupleComponentAccessor(const T& w, const T& x, const T& y, const T& z)
			: TupleComponentAccessor({ w, x, y, z }) {}

		TupleComponentAccessor(const T& w, const TupleData<T, 3, tagVector>& v)
			: TupleComponentAccessor({ w, v.m_v[0], v.m_v[1], v.m_v[2] }) {}

		void Set(const T& w, const T& x, const T& y, const T& z) {
			this->m_v[0] = w; this->m_v[1] = x; this->m_v[2] = y; this->m_v[3] = z;
		}

		const T Scalar() const {
			return this->m_v[0];
		}

		const TupleData<T, 3, tagVector> Vector() const {
			return{ this->m_v[1], this->m_v[2], this->m_v[3] };
		}

		const T& W() const {
			return this->m_v[0];
		}

		T& W() {
			return this->m_v[0];
		}

		const T& X() const {
			return this->m_v[1];
		}

		T& X() {
			return this->m_v[1];
		}

		T& Y() {
			return this->m_v[2];
		}

		const T& Y() const {
			return this->m_v[2];
		}

		T& Z() {
			return this->m_v[3];
		}

		const T& Z() const {
			return this->m_v[3];
		}

	};

	template<class T, int D, typename tag>
	struct TupleOperationsBase : public TupleComponentAccessor < T, D, tag > {
		using Type = TupleOperationsBase < T, D, tag > ;

		using TupleComponentAccessor<T, D, tag>::TupleComponentAccessor;

		TupleOperationsBase() {}

		TupleOperationsBase(const TupleData<T, D, tag>& value)
			: TupleComponentAccessor<T, D, tag>(value) {}

		TupleData<T, D, tag>& operator += (const TupleData<T, D, tag>& value) {
			for (auto i = 0; i < D; ++i) {
				this->m_v[i] += value.m_v[i];
			}
			return *this;
		}

		void Nullify() {
			for (auto& v : this->m_v) {
				v = T{ 0 };
			}
		}

		static TupleData<T, D, tag> Null() {
			TupleData<T, D, tag> res;
			for (auto& v : res.m_v) {
				v = T{ 0 };
			}
			return res;
		}

		void operator -= (const TupleData<T, D, tag>& value) {
			for (auto i = 0; i < D; ++i) {
				this->m_v[i] -= value.m_v[i];
			}
		}

		void operator *= (const T& value) {
			for (auto i = 0; i < D; ++i) {
				this->m_v[i] *= value;
			}
		}

		void operator /= (const T& value) {
			for (auto i = 0; i < D; ++i) {
				this->m_v[i] /= value;
			}
		}

		const TupleData<T, D, tag> operator -() {
			return Negated();
		}

		void Normalize() {
			auto inv_length = T(1) / Length();
			for (auto i = 0; i < D; ++i) {
				this->m_v[i] *= inv_length;
			}
		}

		const Tuple<T, D, tag> Normalized() const {
			auto res = *this;
			res.Normalize();
			return res;
		}

		const T Length() const {
			T sum = SquareLength();
			return Sqrt(sum);
		}

		const T SquareLength() const {
			T sum = 0;
			for (auto& v : this->m_v)
				sum += v*v;
			return sum;
		}

		void Negate() {
			for (auto& v : this->m_v) {
				v = -v;
			}
		}

		const TupleData<T, D, tag> Negated() const {
			auto v = *this;
			v.Negate();
			return v;
		}

		const TupleData<T, D, tagVector> ComponentMult(const TupleData<T, D, tagVector>& v) {
			TupleData<T, D, tagVector> res;
			for (auto i = 0; i < D; ++i) {
				res.m_v[i] = this->m_v[i] * v.m_v[i];
			}
			return res;
		}

		T Dot(const Type& vec) const {
			T res = 0;
			for (auto i = 0; i < D; ++i) {
				res += this->m_v[i] * vec[i];
			}
			return res;
		}

#ifdef USE_QT
        const QString ToString() const {
            QStringList list;
            for (auto i = 0; i < D; ++i){
                list.append(QString::number(this->m_v[i]));
            }
            return QString("(") + list.join("; ") + ")";
        }
#else
		const Core::String ToString() const {
			Core::StringList list;
			for (auto i = 0; i < D; ++i){
				list.Push(Core::String::Convert(this->m_v[i]));
			}
			return L"(" + list.ToString("; ") + L")";
		}
#endif

		TupleData<T, D, tag>& Chop(T eps) {
			for (auto i = 0; i != D; ++i)
				if (Abs(this->m_v[i]) < eps)
					this->m_v[i] = T{ 0 };
			return *this;
		}

		void Refract(const Tuple<T, D, tag>& N, T eta) {
			T k = T{ 1.0 } -eta * eta*(T{ 1.0 } -Dot(N) * Dot(N));
			if (k < T{ 0.0 })
				Nullify();
			else
				*this = eta*(*this) - (eta*Dot(N) + Sqrt(k))*N;
		}

		const Tuple<T, D, tag> Refracted(const Tuple<T, D, tag>& N, T eta) {
			auto res = *this;
			res.Refract(N, eta);
			return res;
		}

		void Reflect(const Tuple<T, D, tag>& N) {
			*this = *this - Dot(N) * N;
		}

		const Tuple<T, D, tag> Reflected(const Tuple<T, D, tag > & N) {
			auto res = *this;
			res.Reflect();
			return res;
		}
	};

	template<class T, int D, typename tag>
	struct TupleOperations : public TupleOperationsBase < T, D, tag > {
		using TupleOperationsBase<T, D, tag>::TupleOperationsBase;

		TupleOperations() {}

		/*TupleOperations(const TupleData<T, D, tag>& value)
			: TupleOperationsBase<T, D, tag>(value) {}*/
	};

	template<class T, int D>
	struct TupleOperations<T, D, tagPoint> : public TupleOperationsBase < T, D, tagPoint > {

		using TupleOperationsBase<T, D, tagPoint>::TupleOperationsBase;

		TupleOperations() {}

		TupleOperations(const TupleData<T, D, tagPoint>& value)
			: TupleOperationsBase<T, D, tagPoint>(value) {}

		const TupleOperations<T, D, tagVector> GetRadiusVector() const {
			TupleOperations<T, D, tagVector> res;
			for (int i = 0; i < D; ++i) {
				res[i] = this->m_v[i];
			}
			return res;
		}
	};

	template<class T>
	struct TupleOperations<T, 2, tagVector> : public TupleOperationsBase < T, 2, tagVector > {
		using TupleOperationsBase<T, 2, tagVector>::TupleOperationsBase;

		TupleOperations() {}

		TupleOperations(const TupleData<T, 2, tagVector>& value)
			: TupleOperationsBase<T, 2, tagVector>(value) {}

        TupleOperations(const TupleData<T, 2, tagPoint>& src, const TupleData<T, 2, tagPoint>& dst) {
            this->m_v[0] = dst.m_v[0] - src.m_v[0];
            this->m_v[1] = dst.m_v[1] - src.m_v[1];
        }


		static bool IsLeftRotation(
			const TupleOperations<T, 2, tagPoint>& a,
			const TupleOperations<T, 2, tagPoint>& b,
			const TupleOperations<T, 2, tagPoint>& c)
		{
			T ux = b.X() - a.X();
			T uy = b.Y() - a.Y();
			T vx = c.X() - a.X();
			T vy = c.Y() - a.Y();

			return ux*vy - uy*vx > T{ 0.0 };
		}

		static bool IsRightRotation(
			const TupleOperations<T, 2, tagPoint>& a,
			const TupleOperations<T, 2, tagPoint>& b,
			const TupleOperations<T, 2, tagPoint>& c)
		{
			T ux = b.X() - a.X();
			T uy = b.Y() - a.Y();
			T vx = c.X() - a.X();
			T vy = c.Y() - a.Y();

			return ux*vy - uy*vx < T{ 0.0 };
		}
	};

	template<class T>
	struct TupleOperations<T, 3, tagVector> : public TupleOperationsBase < T, 3, tagVector > {

		using TupleOperationsBase<T, 3, tagVector>::TupleOperationsBase;

		TupleOperations() {}

		TupleOperations(const TupleData<T, 3, tagVector>& value)
			: TupleOperationsBase<T, 3, tagVector>(value) {}

		const Tuple<T, 3, tagVector> Cross(const TupleOperations<T, 3, tagVector>& vec) const {
			Tuple < T, 3, tagVector > v{
					{
						this->m_v[1] * vec.m_v[2] - this->m_v[2] * vec.m_v[1],
						this->m_v[2] * vec.m_v[0] - this->m_v[0] * vec.m_v[2],
						this->m_v[0] * vec.m_v[1] - this->m_v[1] * vec.m_v[0]
					} };
			return v;
		}

		static const Tuple<T, 3, tagVector> CalculateNormal(
			const Tuple<T, 3, tagPoint>& p1,
			const Tuple<T, 3, tagPoint>& p2,
			const Tuple<T, 3, tagPoint>& p3) {

			return ((p2 - p1).Cross(p3 - p1)).Normalized();
		}

	};

	template<class T>
	struct TupleOperations<T, 4, tagVector> : public TupleOperationsBase < T, 4, tagVector > {

		using TupleOperationsBase<T, 4, tagVector>::TupleOperationsBase;

		TupleOperations() {}

		TupleOperations(const TupleData<T, 4, tagVector>& value)
			: TupleOperationsBase<T, 4, tagVector>(value) {}

		const TupleData<T, 3, tagVector> ToHomogeneus() const {
			TupleData<T, 3, tagVector> res = { this->m_v[0], this->m_v[1], this->m_v[2] };
			for (auto& v : res.m_v) {
				v /= this->m_v[3];
			}
			return res;
		}
	};

	template<class T>
	struct TupleOperations<T, 4, tagQuaternion> : public TupleOperationsBase < T, 4, tagQuaternion > {

		using TupleOperationsBase<T, 4, tagQuaternion>::TupleOperationsBase;

		TupleOperations() {}

		TupleOperations(const TupleData<T, 4, tagQuaternion>& value)
			: TupleOperationsBase<T, 4, tagQuaternion>(value) {}

		const TupleData<T, 4, tagQuaternion> Conjugated() const {
			return (this->m_v[0], -this->m_v[1], -this->m_v[2], -this->m_v[3]);
		}

		void Conjugate() {
			this->m_v[1] = -this->m_v[1];
			this->m_v[2] = -this->m_v[2];
			this->m_v[3] = -this->m_v[3];
		}

		const TupleData<T, 3, tagVector> Rotate(const TupleComponentAccessor<T, 3, tagVector>& v) const {
			TupleOperations<T, 4, tagQuaternion> p{ 0, v.X(), v.Y(), v.Z() };
			TupleOperations<T, 4, tagQuaternion> inv_q = this->Inversed();
			const TupleOperations<T, 4, tagQuaternion>& q = *this;

			p = q * p * inv_q;

			return{ p.X(), p.Y(), p.Z() };
		}

		const Tuple<T, 4, tagQuaternion> Inversed() const {
			T l = this->SqrLength();
			if (l == 0.0f) {
				return{ 0, 0, 0, 0 };
			}
			else {
				TupleOperations<T, 4, tagQuaternion> q = Conjugated();
				return q / l;
			}
		}

		void operator += (const TupleComponentAccessor<T, 4, tagQuaternion>& v)
		{
			this->m_v[0] += v[0];
			this->m_v[1] += v[1];
			this->m_v[2] += v[2];
			this->m_v[3] += v[3];
		}

		void operator -= (const TupleComponentAccessor<T, 4, tagQuaternion>&  v)
		{
			this->m_v[0] -= v[0];
			this->m_v[1] -= v[1];
			this->m_v[2] -= v[2];
			this->m_v[3] -= v[3];
		}

		void operator *= (const TupleComponentAccessor<T, 4, tagQuaternion>& v)
		{
			T w1 = this->W(); T w2 = v.W();
			T x1 = this->X(); T x2 = v.X();
			T y1 = this->Y(); T y2 = v.Y();
			T z1 = this->Z(); T z2 = v.Z();
			T w = w1*w2 - x1*x2 - y1*y2 - z1*z2;
			T x = w1*x2 + x1*w2 + y1*z2 - z1*y2;
			T y = w1*y2 - x1*z2 + y1*w2 + z1*x2;
			T z = w1*z2 + x1*y2 - y1*x2 + z1*w2;

			this->m_v[0] = w;
			this->m_v[1] = x;
			this->m_v[2] = y;
			this->m_v[3] = z;
		}

		void operator *= (T v)
		{
			this->m_v[0] *= v;
			this->m_v[1] *= v;
			this->m_v[2] *= v;
			this->m_v[3] *= v;
		}

		void operator /= (T v)
		{
			this->m_v[0] /= v;
			this->m_v[1] /= v;
			this->m_v[2] /= v;
			this->m_v[3] /= v;
		}
	};

	template<class T, int D, typename tag>
	class Tuple : public TupleOperations < T, D, tag > {
	public:
		using TupleOperations<T, D, tag>::TupleOperations;

		Tuple() {}

		Tuple(const TupleData<T, D, tag>& value)
			: TupleOperations<T, D, tag>(value) {}
	};

	template<class T, int D, typename tag>
	const Tuple<T, D, tag> operator + (const Tuple<T, D, tag>& l, const Tuple<T, D, tag>& r) {
		Tuple<T, D, tag> res{ l };
		res += r;
		return res;
	}

	template<class T, int D, typename tag>
	const Tuple<T, D, tag> operator - (const Tuple<T, D, tag>& l, const Tuple<T, D, tag>& r) {
		Tuple<T, D, tag> res{ l };
		res -= r;
		return res;
	}

	template<class T, int D>
	const Tuple<T, D, tagVector> operator - (const Tuple<T, D, tagPoint>& l, const Tuple<T, D, tagPoint>& r) {
		Tuple<T, D, tagVector> res;
		for (auto i = 0; i < D; ++i) {
			res[i] = l[i] - r[i];
		}
		return res;
	}

	template<class T, int D>
	const Tuple<T, D, tagPoint> operator + (const Tuple<T, D, tagPoint>& l, const Tuple<T, D, tagVector>& r) {
		Tuple<T, D, tagPoint> res;
		for (auto i = 0; i < D; ++i) {
			res[i] = l[i] + r[i];
		}
		return res;
	}

	template<class T, int D>
	const Tuple<T, D, tagPoint> operator - (const Tuple<T, D, tagPoint>& l, const Tuple<T, D, tagVector>& r) {
		Tuple<T, D, tagPoint> res;
		for (auto i = 0; i < D; ++i) {
			res[i] = l[i] - r[i];
		}
		return res;
	}

	template<class T, int D, typename tag>
	const Tuple<T, D, tag> operator * (const Tuple<T, D, tag>& l, const T& r) {
		Tuple<T, D, tag> res{ l };
		res *= r;
		return res;
	}

	template<class T, int D, typename tag>
	const Tuple<T, D, tag> operator * (const T& l, const Tuple<T, D, tag>& r) {
		Tuple<T, D, tag> res{ r };
		res *= l;
		return res;
	}

	template<class T, int D, typename tag>
	const Tuple<T, D, tag> operator / (const Tuple<T, D, tag>& l, const T& r) {
		Tuple<T, D, tag> res{ l };
		res /= r;
		return res;
	}

	template<class T, int D, typename tag>
	bool operator == (const Tuple<T, D, tag>& l, const Tuple<T, D, tag>& r) {
		return l.IsEqual(r);
	}

	template<class T, int D, typename tag>
	bool operator != (const Tuple<T, D, tag>& l, const Tuple<T, D, tag>& r) {
		return !l.IsEqual(r);
	}

	template<class T, int D, typename tag>
	bool operator == (const TupleData<T, D, tag>& l, const TupleData<T, D, tag>& r) {
		return l.IsEqual(r);
	}

	template<class T, int D, typename tag>
	bool operator != (const TupleData<T, D, tag>& l, const TupleData<T, D, tag>& r) {
		return !l.IsEqual(r);
	}

	template<class T, int D, typename tag>
	bool operator == (const TupleData<T, D, tag>& l, const Tuple<T, D, tag>& r) {
		return l.IsEqual(r);
	}

	template<class T, int D, typename tag>
	bool operator != (const TupleData<T, D, tag>& l, const Tuple<T, D, tag>& r) {
		return !l.IsEqual(r);
	}

	template<class T, int D, typename tag>
	bool operator == (const Tuple<T, D, tag>& l, const TupleData<T, D, tag>& r) {
		return l.IsEqual(r);
	}

	template<class T, int D, typename tag>
	bool operator != (const Tuple<T, D, tag>& l, const TupleData<T, D, tag>& r) {
		return !l.IsEqual(r);
	}
}
PUNK_ENGINE_END

#endif	//	_H_MATH_TUPLE
