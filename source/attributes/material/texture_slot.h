#ifndef _H_PUNK_VIRTUAL_TEXTURE_SLOT
#define _H_PUNK_VIRTUAL_TEXTURE_SLOT

#include <config.h>
#include <math/vec3.h>
#include <string/string.h>
#include "itexture_slot.h"
#include "inormal_texture_slot.h"
#include "idiffuse_texture_slot.h"
#include "ispecular_intensity_texture_slot.h"

PUNK_ENGINE_BEGIN
namespace Attributes
{
    class PUNK_ENGINE_LOCAL TextureSlot : public IDiffuseTextureSlot, public INormalTextureSlot, public ISpecularIntensityTextureSlot
    {
    public:

        /**
         * @brief TextureSlot Create texture slot as part of the specified material
         * @param owner Material that owns this slot. Material is responsible for deleting the texture slot.
         */
        TextureSlot();
		virtual ~TextureSlot();

		void SetScale(const Math::vec3& value) override;
		const Math::vec3& GetScale() const override;
		void SetFilename(const Core::String& value) override;
		const Core::String& GetFilename() const override;
		void SetFactor(float value) override;
		float GetFactor() const override;

    private:
        Math::vec3 m_scale;
        Core::String m_image_filename;
		float m_factor{ 1.0f };
    };
}
PUNK_ENGINE_END

#endif // TEXTURE_SLOT_H
