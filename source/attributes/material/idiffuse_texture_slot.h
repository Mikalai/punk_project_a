#ifndef _H_IDIFFUSE_TEXTURE_SLOT
#define _H_IDIFFUSE_TEXTURE_SLOT

#include <config.h>
#include "itexture_slot.h"

PUNK_ENGINE_BEGIN
namespace Attributes {

	DECLARE_PUNK_GUID(IID_IDiffuseTextureSlot, "5E07C8F2-AC4A-41A8-8507-5F25749BAE09");

	class IDiffuseTextureSlot : public ITextureSlot {
	public:
		virtual void SetTexture(Graphics::ITexture2D* value) = 0;
		virtual Graphics::ITexture2D* GetTexture() = 0;
	};
}
PUNK_ENGINE_END

#endif	//	_H_IDIFFUSE_TEXTURE_SLOT