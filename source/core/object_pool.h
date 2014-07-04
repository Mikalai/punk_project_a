#ifndef _H_CORE_OBJECT_POOL
#define _H_CORE_OBJECT_POOL

#include <map>
#include <config.h>
#include "error/module.h"

PUNK_ENGINE_BEGIN
namespace Core {
	
	template < typename Key, typename Value >
	class ObjectPool {
	public:
        
		bool HasValue(const Key& key) {
			auto it = m_container.find(key);
			return it != m_container.end();
		}

		Core::Pointer<Value> GetValue(const Key& key) {
			Core::Pointer<Value> value{ nullptr, Core::DestroyObject };
			auto it = m_container.find(key);
			if (it != m_container.end())
				value = it->second.m_object;
			return value;
		}

		void AddValue(const Key& key, Core::Pointer<Value> value) {
			if (HasValue(key))
				throw Error::CoreException("Key already in pool");
			m_container[key] = Cache{ value };
		}

		void RemoveValue(const Key& key) {
			auto it = m_container.find(key);
            if (it == m_container.end())
				throw Error::CoreException("Key was not added to pool");
			m_container.erase(it);
		}

	private:		

		struct Cache {
			Cache()
				: m_object{ nullptr, Core::DestroyObject }
			{}

			Cache(Core::Pointer<Value> object)
				: m_object{ object }
			{}

			Core::Pointer<Value> m_object{ nullptr, Core::DestroyObject };
		};
		std::map<Key, Cache> m_container;
	};
}
PUNK_ENGINE_END

#endif	//	_H_CORE_OBJECT_POOL
