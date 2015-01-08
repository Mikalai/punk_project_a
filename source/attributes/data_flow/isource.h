#ifndef _H_ISOURCE
#define _H_ISOURCE

#include <config.h>
#include <system/factory/interface.h>

#include "iaccessor.h"

PUNK_ENGINE_BEGIN
namespace Attributes {
	
	DECLARE_PUNK_GUID(CLSID_Source, "402E4B88-3ECA-4F9C-A92B-B4138996AA47");
	DECLARE_PUNK_GUID(IID_ISource, "3438C257-672E-4FB8-9E4B-3DF820B7B950");

	class IArray;	

	class ISource : public Core::IObject {
	public:
		virtual const Core::String GetId() const = 0;
		virtual void SetId(const Core::String& value) = 0;
		virtual const Core::String GetName() const = 0;
		virtual void SetName(const Core::String& value) = 0;		
		virtual void SetAccessor(IAccessorPtr value) = 0;
		virtual IAccessorPtr GetAccessor() = 0;
		virtual const IAccessorPtr GetAccessor() const = 0;
		virtual IArrayPtr GetArray() = 0;
		virtual const IArrayPtr GetArray() const = 0;
		virtual void SetArray(IArrayPtr value) = 0;
	};

	using ISourcePtr = Core::Pointer < ISource > ;

	inline ISourcePtr NewSource() {
		return System::CreateInstancePtr<ISource>(CLSID_Source, IID_ISource);
	}
}
PUNK_ENGINE_END

#endif	//	_H_ISOURCE