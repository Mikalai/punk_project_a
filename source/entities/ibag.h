#ifndef H_PUNK_ENTITY_IBAG
#define H_PUNK_ENTITY_IBAG

#include <config.h>
#include <iobject.h>

PUNK_ENGINE_BEGIN
namespace Entities {
	
	class IShape;

	class IBeg : public Core::IObject {
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