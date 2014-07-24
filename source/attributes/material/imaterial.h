#ifndef _H_IMATERIAL
#define _H_IMATERIAL

#include <core/object.h>
#include <math/forward.h>
#include <string/string.h>
#include "idiffuse_texture_slot.h"
#include "inormal_texture_slot.h"
#include "ispecular_intensity_texture_slot.h"

PUNK_ENGINE_BEGIN
namespace Attributes {
	class ITextureSlot;

	DECLARE_PUNK_GUID(IID_IMaterial, "A62FF5E9-6F01-4094-AFEA-CEB9D4F1C3BD");
	DECLARE_PUNK_GUID(CLSID_Material, "D2F06586-C99F-4CBA-91DD-F0E8C7AA3EC7");

	class IMaterial : public Core::IObject
	{
	public:
		virtual void SetDiffuseTextureSlot(Core::Pointer<IDiffuseTextureSlot> value) = 0;
		virtual void SetNormalTextureSlot(Core::Pointer<INormalTextureSlot> value) = 0;
		virtual void SetSpecularTextureSlot(Core::Pointer<ISpecularIntensityTextureSlot> value) = 0;
		virtual Core::Pointer<IDiffuseTextureSlot> GetDiffuseTextureSlot() = 0;
		virtual Core::Pointer<INormalTextureSlot> GetNormalTextureSlot() = 0;
		virtual Core::Pointer<ISpecularIntensityTextureSlot> GetSpecularTextureSlot() = 0;
		virtual void SetDiffuseColor(const Math::vec4& color) = 0;
		virtual void SetSpecularColor(const Math::vec4& color) = 0;
		virtual void SetSpecularFactor(float value) = 0;
		virtual void SetName(const Core::String& name) = 0;		
		virtual const Math::vec4& GetDiffuseColor() const = 0;
		virtual const Math::vec4& GetSpecularColor() const = 0;
		virtual float GetSpecularFactor() const = 0;
		virtual const Core::String& GetName() const = 0;
		virtual void SetAlpha(float value) = 0;
		virtual float GetAlpha() const = 0;
		virtual void SetAmbient(float value) = 0;
		virtual float GetAmbient() const = 0;
		virtual void SetDiffuseIntensity(float value) = 0;
		virtual float GetDiffuseIntensity() const = 0;
		virtual void SetDarkness(float value) = 0;
		virtual float GetDarkness() const = 0;
		virtual void SetDiffuseFresnel(float value) = 0;
		virtual float GetDiffuseFresnel() const = 0;
		virtual void SetDiffuseFresnelFactor(float value) = 0;
		virtual float GetDiffuseFresnelFactor() const = 0;
		virtual void SetEmit(float value) = 0;
		virtual float GetEmit() const = 0;
		virtual void SetMirrorColor(Math::vec4 value) = 0;
		virtual const Math::vec4 GetMirrorColor() const = 0;
		virtual void SetRoughness(float value) = 0;
		virtual float GetRoughness() const = 0;
		virtual void SetSpecularAlpha(float value) = 0;
		virtual float GetSpecularAlpha() const = 0;
		virtual void SetSpecularIntensity(float value) = 0;
		virtual float GetSpecularIntensity() const = 0;
		virtual void SetSpecularIndexOfRefraction(float value) = 0;
		virtual float GetSpecularIndexOfRefraction() const = 0;
		virtual void SetSpecularSlope(float value) = 0;
		virtual float GetSpecularSlope() const = 0;
		virtual void SetTranslucency(float value) = 0;
		virtual float GetTranslucency() const = 0;		
	};	
}
PUNK_ENGINE_END

#endif	//	_H_IMATERIAL