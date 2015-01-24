#ifndef _H_VALUE_MATH
#define _H_VALUE_MATH

#include <string/string.h>

PUNK_ENGINE_BEGIN
namespace Math {

	template<class T>
	class Value {
	public:

		Value()
			: m_value{ 0 }
		{}

		explicit Value(T v)
			: m_value{ v }
		{}

		const Core::String& GetSid() const {
			return m_sid;
		}

		void SetSid(const Core::String& value) {
			m_sid = value;
		}

		void SetValue(T value) {
			m_value = value;
		}

		T& GetValue() {
			return m_value;
		}
		
		const T& GetValue() const {
			return m_value;
		}

		operator T() {
			return m_value;
		}

		Value& operator = (T value) {
			m_value = value;
			return *this;
		}

	private:
		Core::String m_sid;
		T m_value{ 0 };
	};

	template<class T>
	inline bool operator == (const Value<T>& l, T r) {
		return l.GetValue() == r;
	}

	template<class T>
	inline bool operator == (T l, const Value<T>& r) {
		return r.GetValue() == l;
	}

	template<class T>
	inline Value<T> operator / (const Value<T>& l, T r) {
		Value<T> res;
		res.SetValue(l.GetValue() / r);
		res.SetSid(l.GetSid());
		return res;
	}

	using realf = Value < float > ;
}
PUNK_ENGINE_END

#endif	//	_H_VALUE_MATH