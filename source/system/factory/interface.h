#ifndef _H_FACTORY_INTERFACE
#define _H_FACTORY_INTERFACE

#include <config.h>
#include <core/iobject.h>

PUNK_ENGINE_BEGIN
namespace System {

	class IFactory;

	template<class I> extern Core::Pointer<I> CreateInstancePtr(const Core::Guid& clsid, const Core::Guid& iid);

#define PUNK_INSTANCE_BEGIN(I) \
	template<class T> struct Instance; \
	template<> \
	struct Instance<I> {

#define PUNK_INSTANCE_CREATE(I, M, CLSID, IID) \
	static Core::Pointer<I> New##M() { \
	return System::CreateInstancePtr<I>(CLSID, IID); }

#define PUNK_INSTANCE_END() }

}
PUNK_ENGINE_END

#endif	//	_H_FACTORY_INTERFACE