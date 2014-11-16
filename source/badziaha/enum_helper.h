#ifndef _H_ENUM_SIZE
#define _H_ENUM_SIZE

template<class T>
struct enum_size {
	enum {Value = (int)T::End};
};

template<class T>
inline int enum_index(T value) {
	return (int)value;
}

template<class T>
inline T enum_value(int index) {
	return (T)index;
}

#endif	//	_H_ENUM_SIZE