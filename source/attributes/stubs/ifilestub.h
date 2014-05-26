#ifndef _H_IFILE_STUB
#define _H_IFILE_STUB

#include <config.h>
#include <core/iobject.h>

PUNK_ENGINE_BEGIN
namespace Attributes {

	DEFINE_PUNK_GUID(IID_IFileStub, "FC0CCDCD-D26B-4BDE-A72B-A671C7A98450");

	class IFileStub : public virtual Core::IObject {
	public:
		virtual void SetFilename(const Core::String& value) = 0;
		virtual const Core::String GetFilename() = 0;
	};
}
PUNK_ENGINE_END

#endif	//	_H_IFILE_STUB