#ifndef _H_ENUM_SIZE
#define _H_ENUM_SIZE

template<class T>
struct enum_size {
	enum {Value = (int)T::End};
};

template<class T>
constexpr int enum_index(T value) {
	return (int)value;
}

#endif	//	_H_ENUM_SIZE