#ifndef H_PUNK_ENTITY_IBAG
#define H_PUNK_ENTITY_IBAG

#include <config.h>
#include <core/iobject.h>

PUNK_ENGINE_BEGIN
namespace Entities {
	
	class IShape;

	DECLARE_PUNK_GUID(IID_IBag, "844B7BCC-1536-4D03-90C0-4AE631E438EE");

	DECLARE_PUNK_GUID(CLSID_Bag, "E9F9D795-35A2-4FB6-85B7-143DE094062A");
	class IBag : public Core::IObject {
	public:
		virtual void SetMaxVolume(double value) = 0;
		virtual double GetMaxVolume() const = 0;
		virtual bool CanAddItem(IShape* item) const = 0;
		virtual double GetFreeVolume() const = 0;
		//virtual double Get
	};
}
PUNK_ENGINE_END

#endif	//	H_PUNK_ENTITY_IBAG