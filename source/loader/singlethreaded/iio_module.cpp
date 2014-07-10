#include <core/iobject_impl.h>
#include <loader/parser/parse_punk_file.h>
#include <loader/parser/parse_anything.h>
#include "iio_module.h"

PUNK_ENGINE_BEGIN
namespace IoModule {

	class IoModuleImpl : public IIoModule {
	public:
		//	IObject
		void QueryInterface(const Core::Guid& type, void** object) override {
			Core::QueryInterface(this, type, object, { Core::IID_IObject, System::IID_IModule, IID_IIoModule });
		}

		std::uint32_t AddRef() override {
			return m_ref_count.fetch_add(1);
		}

		std::uint32_t Release() override {
			auto v = m_ref_count.fetch_sub(1) - 1;
			if (!v)
				delete this;
			return v;
		}

		//	IIoModule
		Core::Pointer<Core::IObject> Parse(const Core::String& path) {
			return ParsePunkFile(path);
		}

		Core::Pointer<Core::IObject> Parse(Core::Buffer& buffer) {
			return ParseAnything(buffer);
		}

		void Serialize(Core::Pointer<Core::IObject> object, const Core::String& path) {
			auto serializable = Core::QueryInterfacePtr<System::ISerializable>(System::IID_ISerializable);
			
		}

		void Serialize(Core::Pointer<Core::IObject> object, Core::Buffer& buffer) override {
		}

		Core::Pointer<Core::IObject> Deserialize(const Core::String& path) override {
		}

		Core::Pointer<Core::IObject> Deserialize(Core::Buffer& buffer) override {

		}

	private:
		std::atomic<std::uint32_t> m_ref_count;
	};

	IoModuleImpl g_io_module;

	extern "C" PUNK_ENGINE_API System::IModule* GetPunkModule() {
		return &g_io_module;
	}
}
PUNK_ENGINE_END
