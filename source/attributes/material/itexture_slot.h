#ifndef _H_PUNK_VIRTUAL_ITEXTURE_SLOT
#define _H_PUNK_VIRTUAL_ITEXTURE_SLOT

#include <config.h>
#include <core/iobject.h>
#include <math/vec3.h>
#include <string/string.h>
#include <graphics/texture/module.h>

PUNK_ENGINE_BEGIN
namespace Attributes
{
	class Material;

	class ITextureSlot : public virtual Core::IObject
	{
	public:

		virtual void SetScale(const Math::vec3& value) = 0;
		virtual const Math::vec3& GetScale() const = 0;
		virtual void SetFilename(const Core::String& value) = 0;
		virtual const Core::String& GetFilename() const = 0;
		virtual void SetDiffuseFactor(float value) = 0;
		virtual float GetDiffuseFactor() const = 0;
		virtual void SetNormalFactor(float value) = 0;
		virtual float GetNormalFactor() const = 0;
		virtual void SetSpecularIntensityFactor(float value) = 0;
		virtual float GetSpecularIntensityFactor() const = 0;
		virtual bool IsDiffuseMapSlot() const = 0;
		virtual bool IsNormalMapSlot() const = 0;
		virtual bool IsSpecularIntensityMapSlot() const = 0;
		virtual void MarkAsDiffuseMapSlot(bool value) = 0;
		virtual void MarkAsNormalMapSlot(bool value) = 0;
		virtual void MarkAsSpecularIntensityMapSlot(bool value) = 0;
	};
}
PUNK_ENGINE_END

#endif // TEXTURE_SLOT_H
