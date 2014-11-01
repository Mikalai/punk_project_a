#ifndef _H_ICOLLECTION_IMPL
#define _H_ICOLLECTION_IMPL

#include <config.h>
#include <core/iobject.h>
#include "icollection.h"
#include <core/iserializable.h>
#include <system/factory/module.h>
#include <string/buffer.h>

PUNK_ENGINE_BEGIN
namespace Attributes {

	DECLARE_PUNK_GUID(CLSID_Collection, "D5440417-F309-4699-86F7-F61742DF503E");
	template<class T>
	class Collection : public ICollection, Core::ISerializable {
	public:

		//	ICollection
		void QueryInterface(const Core::Guid& type, void** object) {
			if (!object)
				return;
			*object = nullptr;

			if (type == Core::IID_IObject) {
				*object = this;
				AddRef();
			}
			if (type == IID_ICollection) {
				*object = this;
				AddRef();
			}
			if (type == Core::IID_ISerializable) {
				*object = (Core::ISerializable*)this;
				AddRef();
			}
		}

		std::uint32_t AddRef() override {
			return m_ref_count.fetch_add(1);
		}

		std::uint32_t Release() override {
			auto v = m_ref_count.fetch_sub(1) - 1;
			if (!v) {
				delete this;
			}
			return v;
		}

		//	ICollection
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

		const Core::Pointer<T> Get(std::uint32_t index) const {
			return m_collection.at(index);
		}

		Core::Pointer<T> Get(std::uint32_t index) {
			return m_collection.at(index);
		}

		//	ISerializable
		void Serialize(Core::Buffer& buffer) override {
			buffer.WritePod(CLSID_Collection);
			Core::Buffer tmp;
			std::uint32_t count = 0;
			for (auto& item : m_collection) {
				auto v = Core::QueryInterfacePtr<Core::ISerializable>(item, Core::IID_ISerializable);
				if (!v.get()) {
					continue;
				}
				v->Serialize(tmp);
				count++;
			}
			buffer.WritePod(count);
			buffer.WriteBuffer(tmp.Data(), tmp.GetSize());
		}

		void Deserialize(Core::Buffer& buffer) override {
			std::uint32_t count = 0;
			buffer.ReadPod(count);
			for (std::uint32_t i = 0; i < count; ++i) {
				Core::Guid clsid;
				buffer.ReadPod(clsid);
				auto v = System::CreateInstancePtr<Core::ISerializable>(clsid, Core::IID_ISerializable);
				if (!v.get())
					continue;
				v->Deserialize(buffer);
				m_collection.push_back(v);
			}
		}
	private:
		std::atomic<std::uint32_t> m_ref_count{ 0 };
		std::vector<Core::Pointer<T>> m_collection;
	};
}
PUNK_ENGINE_END

#endif // _H_ICOLLECTION_IMPL