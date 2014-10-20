#ifndef _H_ICOLLECTION
#define _H_ICOLLECTION

#include <config.h>
#include <core/iobject.h>

PUNK_ENGINE_BEGIN
namespace Entities {

	class ICollection : public Core::IObject {
	public:
		virtual void Add(Core::Pointer<Core::IObject> value) = 0;
		virtual void Remove(Core::Pointer<Core::IObject> value) = 0;
		virtual std::uint32_t Size() const = 0;
		virtual const Core::Pointer<Core::IObject> GetItem(std::uint32_t index) const = 0;
		virtual Core::Pointer<Core::IObject> GetItem(std::uint32_t index) = 0;
	};

	template<class T>
	class Collection : public ICollection {
	public:
		void Add(Core::Pointer<Core::IObject> value) override {
			m_collection.push_back(value);
		}

		void Remove(Core::Pointer<Core::IObject> value) override {
			auto it = std::find(m_collection.begin(), m_collection.end(), value);
			if (it == m_collection.end())
				return;
			m_collection.erase(it);
		}

		std::uint32_t Size() const override {
			return (std::uint32_t)m_collection.size();
		}

		const Core::Pointer<Core::IObject> GetItem(std::uint32_t index) const override {
			return m_collection.at(index);
		}

		Core::Pointer<Core::IObject> GetItem(std::uint32_t index) override {
			return m_collection.at(index);
		}

		const Core::Pointer<T> Get(std::uint32_t index) const override {
			return m_collection.at(index);
		}

		Core::Pointer<T> Get(std::uint32_t index) override {
			return m_collection.at(index);
		}
	private:
		std::vector<Core::Pointer<T>> m_collection;
	};
}
PUNK_ENGINE_END

#endif // _H_ICOLLECTION