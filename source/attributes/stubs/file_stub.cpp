#include <core/ifactory.h>
#include "file_stub.h"

PUNK_ENGINE_BEGIN
namespace Attributes {
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
