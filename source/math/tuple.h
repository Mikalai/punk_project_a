#include <initializer_list>
#include <array>
#include <config.h>
#include <string/string_list.h>
#include "square_root.h"

PUNK_ENGINE_BEGIN
namespace Math {

	struct tagPoint;
	struct tagColor;
	struct tagVector;	

	template<typename T, int D, typename tag>
	struct TupleData {

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
			std::copy_n(list.begin(), D, m_v.end());
		}

		TupleData(const TupleData<T, D, tag>& origin, const TupleData<T, D, tag>& destination) {
			for (auto i = 0; i < D; ++i) {
				m_v[i] = destination[i] - origin[i];
			}
		}

		TupleData<T, D, tag>& operator = (const TupleData<T, D, tag>& value) {
			if (this == &value)
				return *this;
			std::copy(value.m_v.begin(), value.m_v.end(), m_v.begin());
		}

		bool IsEqual(const TupleData<T, D, tag>& v) const {
			for (auto i = 0; i < D; ++i)
				if (m_v[i] != v[i])
					return false;
			return true;
		}

		std::array<T, D> m_v;
	};

	template<typename T, int D, typename tag>
	struct TupleComponentAccessorBase : public TupleData < T, D, tag > {

		template<int D>
		using DataType = TupleData < T, D, tag >;

		using TupleData<T, D, tag>::TupleData;
		
		TupleComponentAccessorBase() {}

		T& operator[] (std::uint32_t index) {
			return m_v[index];
		}

		const T& operator[] (std::uint32_t index) const {
			return m_v[index];
		}

		T& at(std::uint32_t index) {
			return m_v.at(index);
		}

		const T& at(std::uint32_t index) const {
			return m_v.at(index);
		}

		operator T* () {
			return m_v.data();
		}

		operator const T* () const {
			return m_v.data();
		}
	};

	
	template<typename T, int D, typename tag>
	struct TupleComponentAccessor : public TupleComponentAccessorBase < T, D, tag > {
		using TupleComponentAccessorBase<T, D, tag>::TupleComponentAccessorBase;		
	};

	template<typename T>
	struct TupleComponentAccessor<T, 2, tagVector> : public TupleComponentAccessorBase < T, 2, tagVector > {

		using BaseType = TupleComponentAccessorBase < T, 2, tagVector > ;
		using Type = TupleComponentAccessor < T, 2, tagVector > ;		

		using TupleComponentAccessorBase<T, 2, tagVector>::TupleComponentAccessorBase;

		TupleComponentAccessor() {}

		Type(const T& x, const T& y) {
			m_v[0] = x; m_v[1] = y;
		}

		TupleData<T, 2, tagVector>& Set(const T& x, const T& y) {			
			m_v[0] = x; m_v[1] = y;
			return *this;
		}

		const T& X() const {
			return m_v[0];
		}

		T& X() {
			return m_v[0];
		}

		T& Y() {
			return m_v[1];
		}

		const T& Y() const {
			return m_v[1];
		}

		const DataType<2> XY() const {
			return DataType<2>{ { m_v[0], m_v[1] } };
		}

		const DataType<2> YX() const {
			return DataType<2>{ { m_v[1], m_v[0] } };
		}
	};

	template<typename T>
	struct TupleComponentAccessor<T, 3, tagVector> : public TupleComponentAccessor < T, 2, tagVector > {

		using BaseType = TupleComponentAccessor < T, 2, tagVector > ;
		using Type = TupleComponentAccessor < T, 3, tagVector > ;

		using TupleComponentAccessor<T, 2, tagVector>::TupleComponentAccessor;
		
		TupleComponentAccessor() {}

		Type(const T& x, const T& y, const T& z) {
			m_v[0] = x; m_v[1] = y; m_v[2] = z;
		}

		DataType<3>& Set(const T& x, const T& y, const T& z) {
			m_v[0] = x; m_v[1] = y; m_v[2] = z;
			return *this;
		}

		const T& Z() const {
			return m_v[2];
		}

		T& Z() {
			return m_v[2];
		}

		const DataType<2> XZ() const {
			return DataType<2>({ m_v[0], m_v[2] });
		}

		const DataType<2> ZX() const {
			return DataType<2>({ m_v[2], m_v[0] });
		}

		const DataType<2> YZ() const {
			return DataType<2>({ m_v[1], m_v[2] });
		}

		const DataType<2> ZY() const {
			return DataType<2>({ m_v[2], m_v[1] });
		}

		const DataType<3>  XYZ() const {
			return DataType<3>({ m_v[0], m_v[1], m_v[2] });
		}

		const DataType<3> XZY() const {
			return DataType<3>({ m_v[0], m_v[2], m_v[1] });
		}

		const DataType<3> YXZ() const {
			return DataType<3>({ m_v[1], m_v[0], m_v[2] });
		}

		const DataType<3> YZX() const {
			return DataType<3>({ m_v[1], m_v[2], m_v[0] });
		}

		const DataType<3> ZXY() const {
			return DataType<3>({ m_v[2], m_v[0], m_v[1] });
		}

		const DataType<3> ZYX() const {
			return DataType<3>({ m_v[2], m_v[1], m_v[0] });
		}
	};
	/*
	template<typename T>
	struct TupleComponentAccessor<T, 4, tagVector> : public TupleComponentAccessor < T, 3, tagVector > {

		using BaseType = TupleComponentAccessor < T, 3, tagVector > ;
		using Type = TupleComponentAccessor < T, 4, tagVector > ;
		
		template<int D>
		using DataType = TupleData < T, D, tagVector > ;

		using TupleComponentAccessor<T, 4, tagVector>::TupleComponentAccessor;

		Type(const T& x, const T& y, const T& z, const T& w) {
			m_v[0] = x; m_v[1] = y; m_v[2] = z; m_v[3] = w;
		}

		DataType<4>& Set(const T& x, const T& y, const T& z, const T& w) {
			m_v[0] = x; m_v[1] = y; m_v[2] = z; m_v[3] = w;
			return *this;
		}

		const T& W() const {
			return m_v[3];
		}

		T& W() {
			return m_v[3];
		}

		const DataType<2> XW() const {
			return DataType<2>(m_v[0], m_v[3]);
		}

		const DataType<2> WX() const {
			return DataType<2>(m_v[3], m_v[0]);
		}

		const DataType<2> WZ() const {
			return DataType<2>(m_v[3], m_v[2]);
		}

		const DataType<2> ZW() const {
			return DataType<2>(m_v[2], m_v[3]);
		}

		const DataType<2> YW() const {
			return DataType<2>(m_v[1], m_v[3]);
		}

		const DataType<2> WY() const {
			return DataType<2>(m_v[3], m_v[1]);
		}

		const DataType<3> XYW() const {
			return DataType<3>(X(), Y(), W());
		}

		const DataType<3> XZW() const {
			return DataType<3>(X(), Z(), W());
		}

		const DataType<3> XWZ() const {
			return DataType<3>(X(), W(), Z());
		}

		const DataType<3> XWY() const {
			return DataType<3>(X(), W(), Y());
		}

		const DataType<3> YXW() const {
			return DataType<3>(Y(), X(), W());
		}

		const DataType<3> YZW() const {
			return DataType<3>(Y(), Z(), W());
		}

		const DataType<3> YWX() const {
			return DataType<3>(Y(), W(), X());
		}

		const DataType<3> YWZ() const {
			return DataType<3>(Y(), W(), Z());
		}

		const DataType<3> ZXW() const {
			return DataType<3>(Z(), X(), W());
		}

		const DataType<3> ZYW() const {
			return DataType<3>(Z(), Y(), W());
		}

		const DataType<3> ZWX() const {
			return DataType<3>(Z(), W(), X());
		}

		const DataType<3> ZWY() const {
			return DataType<3>(Z(), W(), Y());
		}

		const DataType<3> WXY() const {
			return DataType<3>(W(), X(), Y());
		}

		const DataType<3> WXZ() const {
			return DataType<3>(W(), X(), Z());
		}

		const DataType<3> WYX() const {
			return DataType<3>(W(), Y(), X());
		}

		const DataType<3> WYZ() const {
			return DataType<3>(W(), Y(), Z());
		}

		const DataType<3> WZX() const {
			return DataType<3>(W(), Z(), X());
		}

		const DataType<3> WZY() const {
			return DataType<3>(W(), Z(), Y());
		}

		const DataType<4> XYZW() const {
			return DataType<4>(m_v[0], m_v[1], m_v[2], m_v[3]);
		}

		const DataType<4> XYWZ() const {
			return DataType<4>(m_v[0], m_v[1], m_v[3], m_v[2]);
		}

		const DataType<4> XZYW() const {
			return DataType<4>(m_v[0], m_v[2], m_v[1], m_v[3]);
		}

		const DataType<4> XZWY() const {
			return DataType<4>(m_v[0], m_v[2], m_v[3], m_v[1]);
		}

		const DataType<4> XWYZ() const {
			return DataType<4>(m_v[0], m_v[3], m_v[1], m_v[2]);
		}

		const DataType<4> XWZY() const {
			return DataType<4>(m_v[0], m_v[3], m_v[2], m_v[1]);
		}

		const DataType<4> YXZW() const {
			return DataType<4>(m_v[1], m_v[0], m_v[2], m_v[3]);
		}

		const DataType<4> YXWZ() const {
			return DataType<4>(m_v[1], m_v[0], m_v[3], m_v[2]);
		}

		const DataType<4> YZXW() const {
			return DataType<4>(m_v[1], m_v[2], m_v[0], m_v[3]);
		}

		const DataType<4> YZWX() const {
			return DataType<4>(m_v[1], m_v[2], m_v[3], m_v[0]);
		}

		const DataType<4> YWZX() const {
			return DataType<4>(m_v[1], m_v[3], m_v[2], m_v[0]);
		}

		const DataType<4> YWXZ() const {
			return DataType<4>(m_v[1], m_v[3], m_v[0], m_v[2]);
		}


		const DataType<4> ZXYW() const {
			return DataType<4>(m_v[2], m_v[0], m_v[1], m_v[3]);
		}

		const DataType<4> ZXWY() const {
			return DataType<4>(m_v[2], m_v[0], m_v[3], m_v[1]);
		}

		const DataType<4> ZYXW() const {
			return DataType<4>(m_v[2], m_v[1], m_v[0], m_v[3]);
		}

		const DataType<4> ZYWX() const {
			return DataType<4>(m_v[2], m_v[1], m_v[3], m_v[0]);
		}

		const DataType<4> ZWXY() const {
			return DataType<4>(m_v[2], m_v[3], m_v[0], m_v[1]);
		}

		const DataType<4> ZWYX() const {
			return DataType<4>(m_v[2], m_v[3], m_v[1], m_v[0]);
		}

		const DataType<4> WXYZ() const {
			return DataType<4>(m_v[3], m_v[0], m_v[1], m_v[2]);
		}

		const DataType<4> WXZY() const {
			return DataType<4>(m_v[3], m_v[0], m_v[2], m_v[1]);
		}

		const DataType<4> WYXZ() const {
			return DataType<4>(m_v[3], m_v[1], m_v[0], m_v[2]);
		}

		const DataType<4> WYZX() const {
			return DataType<4>(m_v[3], m_v[1], m_v[2], m_v[0]);
		}

		const DataType<4> WZXY() const {
			return DataType<4>(m_v[3], m_v[2], m_v[0], m_v[1]);
		}

		const DataType<4> WZYX() const {
			return DataType<4>(m_v[3], m_v[2], m_v[1], m_v[0]);
		}
	};

	template<class T, int D, typename tag>
	struct TupleOperationsBase : public TupleComponentAccessor < T, D, tag > {
		using Type = TupleOperationsBase < T, D, tag > ;
		using TupleComponentAccessor<T, D, tag>::TupleComponentAccessor;

		TupleData<T, D>& operator += (const TupleData<T, D>& value) {
			for (auto i = 0; i < D; ++i) {
				m_v[i] += value[i];
			}
			return *this;
		}

		TupleData<T, D>& operator -= (const TupleData<T, D>& value) {
			for (auto i = 0; i < D; ++i) {
				m_v[i] -= value[i];
			}
			return *this;
		}

		TupleData<T, D>& operator *= (const T& value) {
			for (auto i = 0; i < D; ++i) {
				m_v[i] += value;
			}
			return *this;
		}

		TupleData<T, D>& operator /= (const T& value) {
			for (auto i = 0; i < D; ++i) {
				m_v[i] /= value;
			}
			return *this;
		}

		const TupleData<T, D> operator -() {
			return Negated();
		}

		const T Length() const {
			for (auto i = 0; i < D; ++i) {
				m_v[i] += value;
			}
			return *this;
		}

		TupleData<T, D>& Normalize() {
			auto inv_length = T(1) / Length();
			for (auto i = 0; i < D; ++i) {
				m_v[i] *= inv_length;
			}
			return *this;
		}

		const TupleData<T, D> Normalized() const {
			auto res = *this;
			return res.Normalize();
		}

		const T Length() const {
			T sum = SqrLength();
			return Sqrt(sum);
		}

		const T SqrLength() const {
			T sum = 0;
			for (auto& v : m_v)
				sum += v*v;
			return sum;
		}

		TupleData<T, D>& Negate() {
			for (auto& v : m_v) {
				v = -v;
				return *this;
			}
		}

		const TupleData<T, D> Negated() const {
			auto v = *this;
			return v.Negate();
		}

		const DataType<D> ComponentMult(const Type& v) {
			DataType<D> res;
			for (auto i = 0; i < D; ++i) {
				res[i] = m_v[i] * v[i];
			}
			return res;
		}

		T Dot(const Type& vec) {
			T res = 0;
			for (auto i = 0; i < D; ++i) {
				res += m_v[i] * vec[i];
			}
			return res;
		}

		const Core::String ToString() const {
			Core::StringList list;
			list.Push("(");
			for (auto i = 0; i < D; ++i){
				list.Push(Core::String::Convert(m_v[i]));
			}
			list.Pus(")");
			return list.ToString();
		}
	};

	template<class T, int D, typename tag>
	struct TupleOperations : TupleOperationsBase < T, D, tag > {
		using TupleOperationsBase<T, D, tag>::TupleOperationsBase;
	};

	template<class T, int D, typename tag>
	class Tuple : public TupleOperations < T, D, tag > {
		using TupleOperations<T, D, tag>::TupleOperations;
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
	const Tuple<T, D, tag> operator == (const Tuple<T, D, tag>& l, const Tuple<T, D, tag>& r) {
		return l.IsEqual(r);
	}

	template<class T, int D, typename tag>
	const Tuple<T, D, tag> operator != (const Tuple<T, D, tag>& l, const Tuple<T, D, tag>& r) {
		return l.IsEqual(r);
	}*/

}
PUNK_ENGINE_END