#include <system/factory/module.h>
#include "ifile_stub.h"

PUNK_ENGINE_BEGIN
namespace Attributes {

	class PUNK_ENGINE_LOCAL FileStub : public IFileStub {
	public:
		//	IObject
		void QueryInterface(const Core::Guid& type, void** object) override;
		std::uint32_t AddRef() override;
		std::uint32_t Release() override;

		//	IFileStub
		bool IsLoaded() const override { return m_loaded; };
		bool IsLoading() const override { return m_loading; }
		void SetLoading(bool value) override { m_loading = value; m_loaded = !value; }
		void SetLoaded(bool value) override { m_loaded = value; m_loading = !value; }
		void SetFilename(const Core::String& value) override;
		const Core::String GetFilename() override;

		void SetCallback(Core::Pointer<OnLoadedCallback> callback) override {
			if (!callback)
				return;
			m_callback = callback;
		}
		
		Core::Pointer<OnLoadedCallback> GetCallback() override {
			return m_callback;
		}

	private:
		std::atomic<std::uint32_t> m_ref_count{ 0 };
		bool m_loaded{ false };
		bool m_loading{ false };
		Core::String m_filename;
		Core::Pointer<OnLoadedCallback> m_callback{ nullptr, Core::DestroyObject };
	};

	void FileStub::QueryInterface(const Core::Guid& type, void** object) {
		Core::QueryInterface(this, type, object, { Core::IID_IObject, IID_IFileStub });
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

	void FileStub::SetFilename(const Core::String& value) {
		m_filename = value;
	}

	const Core::String FileStub::GetFilename() {
		return m_filename;
	}

	PUNK_REGISTER_CREATOR(IID_IFileStub, (System::CreateInstance<FileStub, IFileStub>));
}
PUNK_ENGINE_END
