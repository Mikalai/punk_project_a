#ifndef _H_IFILE_STUB
#define _H_IFILE_STUB

#include <config.h>
#include <core/iobject.h>

PUNK_ENGINE_BEGIN
namespace Attributes {
	class IFileStub : public virtual Core::IObject {
	public:
		virtual void SetFilename(const Core::String& value) = 0;
		virtual const Core::String GetFilename() = 0;
		virtual bool IsLoaded() const = 0;
		virtual bool IsLoading() const = 0;
		virtual void Unload() const = 0;
		virtual Core::IObject* GetLoadedInstance() = 0;		
	};
}
PUNK_ENGINE_END

#endif	//	_H_IFILE_STUB