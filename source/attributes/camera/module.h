#ifndef _H_PUNK_CAMERA_MODULE
#define _H_PUNK_CAMERA_MODULE

#include "icamera.h"
#include "iperspective_camera.h"
#include "iprojection.h"
#include "iperspective.h"

PUNK_ENGINE_BEGIN
namespace Attributes {

	template<class T> struct To;

	template<> 
	struct To < IProjection > {
		static IProjectionPtr From(IPerspectivePtr value) {
			return Core::QueryInterfacePtr<IProjection>(value, IID_IProjection);
		}
	};
}
PUNK_ENGINE_END


#endif	//	_H_PUNK_CAMERA_MODULE
