#ifndef _H_CONFIG
#define _H_CONFIG

#include <array>
#include <memory>
#include "enum_helper.h"

enum class OptionType {
	EnableCheats,
	TimeScale,
	GlobalFieldWidth,
	GlobalFieldHeight,
	LocalFieldWidth,
	LocalFieldHeight,
	CellSize,
	End
};

class Options final {
	
	union Value {
		bool m_bool;
		float m_float;
		int m_int;
	};

public:
	
	Options();

	template<class T>
	T option(OptionType value) const {
		return reinterpret_cast<const T&>(m_value[enum_index(value)]);
	}

	template<class T>
	void setOption(OptionType type, T value) {
		reinterpret_cast<T&>(m_value[enum_index(type)]) = value;
	}

	static Options* instance() {
		if (!m_instance.get()) {
			m_instance.reset(new Options);
		}
		return m_instance.get();
	}

	static void destroy() {
		m_instance.reset{ nullptr };
	}

private:
	void load();
	static std::unique_ptr<Options> m_instance;	
	std::array<Value, enum_size<OptionType>::Value> m_value;
};

#endif	//	 _H_CONFIG