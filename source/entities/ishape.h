#ifndef H_PUNK_ENTITY_SHAPE
#define H_PUNK_ENTITY_SHAPE

#include <config.h>
#include <core/iobject.h>

PUNK_ENGINE_BEGIN
namespace Entities {

	class IShape : public Core::IObject {
	public:
		virtual void SetMass(double value) = 0;
		virtual double GetMass() const = 0;
		virtual void SetVolume(double value) = 0;
		virtual double GetVolume() const = 0;
	};
}
PUNK_ENGINE_END

#endif	// H_PUNK_ENTITY_SHAPE