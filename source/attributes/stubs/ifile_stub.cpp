#include <core/ifactory.h>
#include "ifile_stub.h"

PUNK_ENGINE_BEGIN
namespace Attributes {

	class PUNK_ENGINE_LOCAL FileStub : public IFileStub {
	public:
		void QueryInterface(const Core::Guid& type, void** object) override;
		bool IsLoaded() const override { return m_loaded; };
		bool IsLoading() const override { return m_loading; }
		void SetLoading(bool value) override { m_loading = value; m_loaded = !value; }
		void SetLoaded(bool value) override { m_loaded = value; m_loading = !value; }
		void SetFilename(const Core::String& value) override;
		const Core::String GetFilename() override;

		void SetCallback(Core::ActionBase<Core::IObject*>* callback) override {
			if (!callback)
				return;
			callback->AddRef();
			m_callback.reset(callback);
		}
		
		Core::ActionBase<Core::IObject*>* GetCallback() override {
			return m_callback.get();
		}

	private:
		bool m_loaded{ false };
		bool m_loading{ false };
		Core::String m_filename;
		Core::UniquePtr<Core::ActionBase<Core::IObject*>, Core::MetaAction> m_callback{ nullptr, Core::ReleaseObject<Core::MetaAction> };
		PUNK_OBJECT_DEFAULT_IMPL(FileStub)
	};

	void FileStub::QueryInterface(const Core::Guid& type, void** object) {
		Core::QueryInterface(this, type, object, { Core::IID_IObject, IID_IFileStub });
	}

	void FileStub::SetFilename(const Core::String& value) {
		m_filename = value;
	}

	const Core::String FileStub::GetFilename() {
		return m_filename;
	}

	PUNK_REGISTER_CREATOR(IID_IFileStub, (Core::CreateInstance<FileStub, IFileStub>));
}
PUNK_ENGINE_END
