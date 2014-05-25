#ifndef _H_CONTAINER
#define _H_CONTAINER

#include <config.h>
#include <vector>
#include "core_error.h"

PUNK_ENGINE_BEGIN
namespace Core {

	template<class T, class Owner = T, class This = Owner>
	class Container {
	public:

		Container(This* _this, Owner* parent)
			: m_owner{ parent }
			, m_this{ _this }
		{			
			if (m_owner)
				m_owner->AddChild(m_this);
		}

		~Container() {
			if (m_owner) {
				m_owner->RemoveChild(m_this);
				m_owner = nullptr;
			}
		}

		void SetOwner(Owner* object) {
			m_owner = object;
		}

		T* GetOwner() {
			return m_owner;
		}

		const T* GetOwner() const {
			return m_owner;
		}

		void AddChild(T* value) {
			if (value == nullptr)
				throw Core::Error::CoreException("Object reference is null");

			auto it = std::find(m_children.begin(), m_children.end(), value);
			if (it != m_children.end())
				return;

			m_children.push_back(value);
			value->SetOwner(m_this);
		}

		void RemoveChild(T* value, bool depth = false) {
			if (value == nullptr)
				throw Core::Error::CoreException("Object reference is null");

			for (auto it = m_children.begin(); it != m_children.end(); ++it)
			{
				if (*it == value)
				{
					m_children.erase(it);
					value->SetOwner(nullptr);
					return;
				}
			}

			if (depth)
			{
				for (T* o : m_children)
				{
					if (o)
					{
						o->RemoveChild(value, depth);
					}
				}
			}
		}

		void RemoveChild(std::uint32_t index) {
			if (index < 0 || index >= (int)m_children.size())
				throw Core::Error::CoreException("Index out of range");
			return RemoveChild(m_children[index]);
		}

		T* GetChild(std::uint32_t index) {
			return m_children[index];
		}

		virtual const T* GetChild(std::uint32_t index) const {
			return m_children[index];
		}

		std::uint32_t GetChildrenCount() const {
			return (std::uint32_t)m_children.size();
		}


	private:
		This* m_this{ nullptr };
		Owner* m_owner{ nullptr };
		std::vector < T* > m_children;
	};
}
PUNK_ENGINE_END

#endif	//	_H_CONTAINER