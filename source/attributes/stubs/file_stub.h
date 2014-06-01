#ifndef _H_FILE_STUB
#define _H_FILE_STUB

#include <config.h>
#include "ifilestub.h"

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
	private:
		bool m_loaded{ false };
		bool m_loading{ false };
		Core::String m_filename;

		PUNK_OBJECT_DEFAULT_IMPL(FileStub)
	};
}
PUNK_ENGINE_END

#endif	//	_H_FILE_STUB