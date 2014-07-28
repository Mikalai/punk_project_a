#ifndef _H_SYSTEM_IMODULE
#define _H_SYSTEM_IMODULE

#include <config.h>
#include <core/iobject.h>

PUNK_ENGINE_BEGIN
namespace System {

	DECLARE_PUNK_GUID(IID_IModule, "443D7D63-702E-40B7-8248-44016E829220");

	class IModule : public Core::IObject {
	public:
		virtual void Create(const Core::Guid& clsid, const Core::Guid& iid, void** object) = 0;
		virtual const Core::String GetName() const = 0;
		virtual const Core::String GetDescription() const = 0;
		virtual const Core::String GetFullpath() const = 0;
		virtual void SetFullpath(const Core::String& value) = 0;

		template<class I>
		Core::Pointer<I> Create(const Core::Guid& clsid, const Core::Guid& iid) {
			Core::Pointer<I> res{ nullptr, Core::DestroyObject };
			I* o = nullptr;
			Create(clsid, iid, (void**)&o);
			if (o) {
				res.reset(o);
			}
			return res;
		}
	};
}

PUNK_ENGINE_END

#endif	//	_H_SYSTEM_IMODULE
