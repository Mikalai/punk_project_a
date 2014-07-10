#ifndef _H_PUNK_VIRTUAL_ITEXTURE_SLOT
#define _H_PUNK_VIRTUAL_ITEXTURE_SLOT

#include <config.h>
#include <math/vec3.h>
#include <string/string.h>
#include <graphics/texture/module.h>
#include <core/iobject.h>

PUNK_ENGINE_BEGIN
namespace Attributes
{
	DECLARE_PUNK_GUID(IID_ITextureSlot, "6040A5FF-D45D-467E-A17D-AF165F5D3CAC");
	DECLARE_PUNK_GUID(CLSID_TextureSlot, "5ECBF1DA-C68B-4ED5-8650-4BB8AA662FB3");

	class ITextureSlot : public Core::IObject
	{
	public:
		virtual void SetScale(const Math::vec3& value) = 0;
		virtual const Math::vec3& GetScale() const = 0;
		virtual void SetFilename(const Core::String& value) = 0;
		virtual const Core::String& GetFilename() const = 0;
		virtual void SetFactor(float value) = 0;
		virtual float GetFactor() const = 0;		
	};
}
PUNK_ENGINE_END

#endif // TEXTURE_SLOT_H
