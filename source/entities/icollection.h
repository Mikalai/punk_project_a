#ifndef _H_ICOLLECTION
#define _H_ICOLLECTION

#include <config.h>
#include <core/iobject.h>

PUNK_ENGINE_BEGIN
namespace Entities {

	DECLARE_PUNK_GUID(IID_ICollection, "90792AAF-5FB0-4872-B569-8EBCD9152666");

	class ICollection : public Core::IObject {
	public:
		virtual void Add(Core::Pointer<Core::IObject> value) = 0;
		virtual void Remove(Core::Pointer<Core::IObject> value) = 0;
		virtual std::uint32_t Size() const = 0;
		virtual const Core::Pointer<Core::IObject> GetItem(std::uint32_t index) const = 0;
		virtual Core::Pointer<Core::IObject> GetItem(std::uint32_t index) = 0;
	};
}
PUNK_ENGINE_END

#endif // _H_ICOLLECTION