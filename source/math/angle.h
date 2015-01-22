#ifndef _H_ANGLE
#define _H_ANGLE

#include "constants.h"
#include "value.h"

PUNK_ENGINE_BEGIN
namespace Math {

	struct tagDegree;
	struct tagRadian;

	template<typename T, typename tag>
	class AngleBase : public Value < T > {
	public:

		AngleBase() {}

		AngleBase(const Value<T>& v)
			: Value<T>( v )
		{}

		AngleBase(T v)
			: Value < T >(v)
		{}

	};

	template<typename T, typename TagFrom, typename TagTo> struct Converter;

	template<typename T>
	struct Converter < T, tagDegree, tagRadian > {
		static T Convert(T from) {
			T result = from / T(180) * PI;
			return result;
		}
	};

	template<typename T>
	struct Converter < T, tagRadian, tagDegree > {
		static T Convert(T from) {
			T result = from / PI * T(180);
			return result;
		}
	};	

	template<class T, typename Tag>
	class AngleOperation : public AngleBase < T, Tag> {
	public:

		AngleOperation()
		{}

		AngleOperation(const AngleBase<T, Tag>& v)
			: AngleBase<T, Tag>(v)
		{}

		AngleOperation(const Value<T>& v)
			: AngleBase < T, Tag > (v)
		{}

		AngleOperation(T v)
			: AngleBase < T, Tag >(v)
		{}

		template<typename ToTag>
		const AngleBase<T, ToTag> To() const {
			T value = this->GetValue();
			T result = Converter<T, Tag, ToTag>::Convert(value);
			AngleBase<T, ToTag> r;
			r.SetValue(result);
			r.SetSid(this->GetSid());
			return r;
		}

		template<typename ToTag>
		static const AngleBase<T, ToTag> To(const AngleBase<T, Tag>& v) {
			T value = v.GetValue();
			T result = Converter<T, Tag, ToTag>::Convert(value);
			AngleBase<T, ToTag> r;
			r.SetValue(result);
			r.SetSid(v.GetSid());
			return r;
		}

		template<typename ToTag>
		static const AngleBase<T, ToTag> To(const Value<T>& v) {
			T value = v.GetValue();
			T result = Converter<T, Tag, ToTag>::Convert(value);
			AngleBase<T, ToTag> r;
			r.SetValue(result);
			r.SetSid(v.GetSid());
			return r;
		}
	};

	template<class T, typename Tag>
	class Angle : public AngleOperation < T, Tag > {
	public:

		Angle() {}

		explicit Angle(const Value<T>& v) 
			: AngleOperation < T, Tag >(v)
		{}

		explicit Angle(T v)
			: AngleOperation < T, Tag >(v)
		{}

		Angle(const AngleBase<T, Tag>& v) 
			: AngleOperation<T, Tag>(v)
		{}
	};

	template<class T>
	using Degree = Angle < T, tagDegree > ;

	template<class T>
	using Radian = Angle < T, tagRadian > ;

	using degf = Degree < float > ;
	using radf = Radian < float > ;

	template<class T, typename Tag>
	inline Angle<T, Tag> operator / (const Angle<T, Tag>& l, T r) {
		Angle<T, Tag> res;
		res.SetValue(l.GetValue() / r);
		res.SetSid(l.GetSid());
		return res;
	}

	template<class T, typename Tag>
	inline Angle<T, Tag> operator * (const Angle<T, Tag>& l, T r) {
		Angle<T, Tag> res;
		res.SetValue(l.GetValue() * r);
		res.SetSid(l.GetSid());
		return res;
	}

	template<class T>
	const Radian<T> DegToRad(const Degree<T>& v) {
		return Converter<T, tagDegree, tagRadian>::Convert(v.GetValue());
	}

	template<class T>
	const Degree<T> RadToDeg(const Radian<T>& v) {
		return Converter<T, tagRadian, tagDegree>::Convert(v.GetValue());
	}
}
PUNK_ENGINE_END

#endif	//	_H_ANGLE