#ifndef _H_IFILE_STUB
#define _H_IFILE_STUB

#include <config.h>
#include <core/action.h>
#include <core/iobject.h>

PUNK_ENGINE_BEGIN
namespace Attributes {

	DECLARE_PUNK_GUID(IID_IFileStub, "FC0CCDCD-D26B-4BDE-A72B-A671C7A98450");
	DECLARE_PUNK_GUID(CLSID_FileStub, "0DC7E7A8-7142-48EA-BE05-DEA79499162C");

	using OnLoadedCallback = Core::ActionBase < Core::Pointer<Core::IObject> > ;

	class IFileStub : public Core::IObject {
	public:
		virtual bool IsLoaded() const = 0;
		virtual bool IsLoading() const = 0;
		virtual void SetLoading(bool value) = 0;
		virtual void SetLoaded(bool value) = 0;
		virtual void SetFilename(const Core::String& value) = 0;
		virtual const Core::String GetFilename() = 0;
		virtual void SetCallback(Core::Pointer<OnLoadedCallback> callback) = 0;
		virtual Core::Pointer<OnLoadedCallback> GetCallback() = 0;
	};
}
PUNK_ENGINE_END

#endif	//	_H_IFILE_STUB