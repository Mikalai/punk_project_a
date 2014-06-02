#ifndef _H_INORMAL_INORMAL_TEXTURE_SLOT
#define _H_INORMAL_INORMAL_TEXTURE_SLOT

#include <config.h>
#include "itexture_slot.h"

PUNK_ENGINE_BEGIN
namespace Attributes {

	DECLARE_PUNK_GUID(IID_INormalTextureSlot, "B2F33B26-83ED-449F-8FD8-034775D51BB2");

	class INormalTextureSlot : public ITextureSlot {
	public:
		virtual void SetTexture(Graphics::ITexture2D* value) = 0;
		virtual Graphics::ITexture2D* GetTexture() = 0;
	};
}
PUNK_ENGINE_END

#endif	//	_H_INORMAL_INORMAL_TEXTURE_SLOT
