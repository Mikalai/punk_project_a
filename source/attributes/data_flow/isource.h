#ifndef _H_ISOURCE
#define _H_ISOURCE

#include <config.h>
#include <string/string.h>

PUNK_ENGINE_BEGIN
namespace Attributes {
	
	class IArray;

	class ISource : public Core::IObject {
	public:
		virtual const Core::String GetId() const = 0;
		virtual void SetId(const Core::String& value) = 0;
		virtual const Core::String GetName() const = 0;
		virtual void SetName(const Core::String& value) = 0;		
	};
}
PUNK_ENGINE_END

#endif	//	_H_ISOURCE