#ifndef _H_ILAW
#define _H_ILAW

#include <config.h>
#include <core/iobject.h>
#include <core/pointer.h>

PUNK_ENGINE_BEGIN
namespace Entities {

	class IActivity;

	class ILaw : public Core::IObject {
	public:
		virtual bool Evaluate(Core::Pointer<IActivity> value);
	};
}

PUNK_ENGINE_END

#endif	//	_H_ILAW