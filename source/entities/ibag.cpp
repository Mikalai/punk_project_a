#include <system/logger/module.h>
#include "ibag.h"
#include "icollection_impl.h"
#include "ishape.h"

PUNK_ENGINE_BEGIN
namespace Entities {

	class Bag : public IBag, public ICollection, public Core::ISerializable {
	public:
		//	IObject
		void QueryInterface(const Core::Guid& type, void** object) override { 
			if (!object)
				return;

			*object = nullptr;
			if (type == Core::IID_IObject) {
				*object = (IBag*)this;
				AddRef();
			}
			if (type == IID_IBag) {
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

		//	IBag
		void SetMaxVolume(double value) override {
			m_max_volume = value;
		}

		double GetMaxVolume() const override {
			return m_max_volume;
		}

		bool CanAddItem(IShape* item) const override {
			auto v = item->GetVolume();
			return v <= m_free_volume;
		}

		double GetFreeVolume() const override {
			return m_free_volume;
		}

		//	ICollection
		void Add(Core::Pointer<Core::IObject> value) override {
			Core::Pointer<IShape> shape = value;
			if (!shape.get()) {
				System::GetDefaultLogger()->Error("Can't add object to the bag because it is not a shape");
				return;
			}
			m_collection.Add(shape);
		}
		
		void Remove(Core::Pointer<Core::IObject> value) override {
			m_collection.Remove(value);
		}

		std::uint32_t Size() const override {
			return m_collection.Size();
		}

		const Core::Pointer<Core::IObject> GetItem(std::uint32_t index) const override {
			return m_collection.GetItem(index);
		}

		Core::Pointer<Core::IObject> GetItem(std::uint32_t index) override {
			return m_collection.GetItem(index);
		}

		//	ISerializable
		void Serialize(Core::Buffer& buffer) override {
			buffer.WritePod(CLSID_Bag);
			buffer.WritePod(m_max_volume);
			buffer.WritePod(m_free_volume);
			m_collection.Serialize(buffer);
		}

		void Deserialize(Core::Buffer& buffer) override {			
			buffer.ReadPod(m_max_volume);
			buffer.ReadPod(m_free_volume);
			m_collection.Deserialize(buffer);
		}

	private:
		std::atomic<std::uint32_t> m_ref_count{ 0 };

		//	IBag
		double m_max_volume{ 10 };
		double m_free_volume{ 10 };

		//	ICollection
		Collection<IShape> m_collection;
	};
}
PUNK_ENGINE_END
