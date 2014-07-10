#include <system/factory/module.h>
#include <string/buffer.h>
#include <core/iserializable.h>
#include "ifile_stub.h"

PUNK_ENGINE_BEGIN
namespace Attributes {

	class PUNK_ENGINE_LOCAL FileStub : public IFileStub, public Core::ISerializable {
	public:
		//	IObject
		void FileStub::QueryInterface(const Core::Guid& type, void** object) {
			if (!object)
				return;

			if (Core::IID_IObject == type) {
				*object = (IFileStub*)this;
				AddRef();
			}
			else if (IID_IFileStub == type) {
				*object = (IFileStub*)this;
				AddRef();
			}
			else if (Core::IID_ISerializable == type) {
				*object = (Core::ISerializable*)this;
				AddRef();
			}
			else
				*object = nullptr;
		}

		std::uint32_t FileStub::AddRef() {
			return m_ref_count.fetch_add(1);
		}

		std::uint32_t FileStub::Release() {
			auto v = m_ref_count.fetch_sub(1) - 1;
			if (!v) {
				delete this;
			}
			return v;
		}

		//	IFileStub
		bool IsLoaded() const override { 
			return m_loaded; 
		};
		
		bool IsLoading() const override { 
			return m_loading; 
		}
		
		void SetLoading(bool value) override { 
			m_loading = value; 
			m_loaded = !value; 
		}
		
		void SetLoaded(bool value) override {
			m_loaded = value; 
			m_loading = !value; 
		}
		
		void FileStub::SetFilename(const Core::String& value) override {
			m_filename = value;
		}

		const Core::String FileStub::GetFilename() override {
			return m_filename;
		}

		void SetCallback(Core::Pointer<OnLoadedCallback> callback) override {
			if (!callback)
				return;
			m_callback = callback;
		}

		Core::Pointer<OnLoadedCallback> GetCallback() override {
			return m_callback;
		}

		//	ISerializable
		void Serialize(Core::Buffer& buffer) override {
			buffer.WriteBuffer(CLSID_FileStub.ToPointer(), sizeof(CLSID_FileStub));
			buffer.WriteString(m_filename);
		}

		void Deserialize(Core::Buffer& buffer) override {
			m_filename = buffer.ReadString();
		}

	private:
		std::atomic<std::uint32_t> m_ref_count{ 0 };
		bool m_loaded{ false };
		bool m_loading{ false };
		Core::String m_filename;
		Core::Pointer<OnLoadedCallback> m_callback{ nullptr, Core::DestroyObject };
	};		

	PUNK_REGISTER_CREATOR(CLSID_FileStub, (System::CreateInstance<FileStub, IFileStub>));
}
PUNK_ENGINE_END
