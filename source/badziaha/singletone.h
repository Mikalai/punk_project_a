#ifndef _H_SINGLETONE
#define _H_SINGLETONE

#include <memory>

template<class T>
class Singletone {
public:

	static T* instance() {
		if (!m_instance.get())
			m_instance.reset(new T);
		return m_instance.get();
	}

	static void destroy() {
		m_instance.reset();
	}

private:
	static std::unique_ptr<T> m_instance;
};

template<class T>
std::unique_ptr<T> Singletone<T>::m_instance;

#endif	//	_H_SINGLETONE