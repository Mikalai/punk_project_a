#ifndef _H_CORE_OBJECT_POOL
#define _H_CORE_OBJECT_POOL

#include <config.h>
#include <map>
#include "error/module.h"

PUNK_ENGINE_BEGIN
namespace Core {
	template < class Key, class Value > 
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
				throw Core::CoreException("Key already in pool");
			m_container[key] = value;
		}

		void RemoveValue(const Key& key) {
			auto it = m_container.find(key);
			if (it == m_contaner.end())
				throw Core::CoreException("Key was not added to pool");
			m_container.erase(it);
		}

	private:

		bool GetValue(const Key& key, Value* value) {
			auto it = m_container.find(key);
			if (it == m_contaner.end())
				return false;
			if (value)
				*value = it.second;
		}

		std::map<Key, Value> m_container;
	}
}
PUNK_ENGINE_END

#endif	//	_H_CORE_OBJECT_POOL