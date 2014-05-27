#ifndef _H_INORMAL_ISPECULAR_INTENSITY_TEXTURE_SLOT
#define _H_INORMAL_ISPECULAR_INTENSITY_TEXTURE_SLOT

#include <config.h>
#include "itexture_slot.h"

PUNK_ENGINE_BEGIN
namespace Attributes {

	DECLARE_PUNK_GUID(IID_ISpecularIntensityTextureSlot, "5CB07BFC-9A2D-4E1D-BE45-58395FE4AC90");

	class ISpecularIntensityTextureSlot : public virtual ITextureSlot {
	public:
	};
}
PUNK_ENGINE_END

#endif	//	_H_INORMAL_ISPECULAR_INTENSITY_TEXTURE_SLOT
