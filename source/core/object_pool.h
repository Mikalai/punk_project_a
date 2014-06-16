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
			return GetValue(key, nullptr);
		}

		Value GetValue(const Key& key) {
			Value value;
			if (GetValue(key, &value))
				return value;
			throw Error::CoreException("Key not found");
		}

		void AddValue(const Key& key, Value value) {
			if (HasValue(key))
				throw Error::CoreException("Key already in pool");
			m_container[key] = value;
		}

		void RemoveValue(const Key& key) {
			auto it = m_container.find(key);
			if (it == m_contaner.end())
				throw Error::CoreException("Key was not added to pool");
			m_container.erase(it);
		}

	private:

		bool GetValue(const Key& key, Value* value) {
			std::map<Key, Value>::iterator it2 = m_container.find(key);
			if (it2 == m_container.end())
				return false;
			it2->second;
			if (value)
				*value = it2->second;
			return true;
		}

		std::map<Key, Value> m_container;
	};
}
PUNK_ENGINE_END

#endif	//	_H_CORE_OBJECT_POOL