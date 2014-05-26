#ifndef _H_FILE_STUB
#define _H_FILE_STUB

#include <config.h>
#include "ifilestub.h"

PUNK_ENGINE_BEGIN
namespace Attributes {

	class PUNK_ENGINE_LOCAL FileStub : public IFileStub {
	public:
		void QueryInterface(const Core::Guid& type, void** object) override;
		void SetFilename(const Core::String& value) override;
		const Core::String GetFilename() override;
	private:
		Core::String m_filename;

		PUNK_OBJECT_DEFAULT_IMPL(FileStub)
	};
}
PUNK_ENGINE_END

#endif	//	_H_FILE_STUB