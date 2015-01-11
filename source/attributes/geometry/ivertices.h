#ifndef _H_GEOMETRY_VERTICES
#define _H_GEOMETRY_VERTICES

#include <config.h>
#include <system/factory/interface.h>

PUNK_ENGINE_BEGIN
namespace Attributes {
	
	class IVertices : public Core::IObject {
	public:
		virtual void SetId(const Core::String& value) = 0;
		virtual const Core::String GetId() const = 0;
		virtual void SetName(const Core::String& value) = 0;
		virtual const Core::String GetName() const = 0;

	};
}
PUNK_ENGINE_END

#endif	//	_H_GEOMETRY_VERTICES