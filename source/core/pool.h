#ifndef _H_PUNK_POOL
#define _H_PUNK_POOL

#include <stddef.h>
#include <stdlib.h>
#include <memory.h>
#include <deque>
#include <config.h>

#ifdef _DEBUG
#include <iostream>
#endif	

PUNK_ENGINE_BEGIN
namespace Core {

	template<class T>
	class Pool {
	public:

		Pool() {
#ifdef _DEBUG            
			std::cout << "Pool created for " << typeid(T).name() << std::endl;
#endif
		}

		~Pool() {
			Clear();
		}

		void* Alloc() {
			if (m_free.empty()) {
#ifdef _DEBUG            
				std::cout << "Allocation requested for " << typeid(T).name() << " " << sizeof(T) << " bytes" << std::endl;
#endif
				auto size = sizeof(T);
				void* result = malloc(size);
				memset(result, 0, size);
				return result;
			}
			void* result = m_free.front();
			memset(result, 0, sizeof(T));
			m_free.pop_front();
			return result;
		}

		void Free(void* value) {
			m_free.push_back(value);
		}

		void Clear() {
#ifdef _DEBUG        
			std::cout << "Clear pool " << typeid(T).name() << std::endl;
#endif
			while (!m_free.empty()) {
				free(m_free.back());
				m_free.pop_back();
			}
		}

	private:
		std::deque<void*> m_free;
#ifdef _DEBUG
		const char* m_name;
#endif
	};
}
PUNK_ENGINE_END

#endif  //  _H_PUNK_POOL
