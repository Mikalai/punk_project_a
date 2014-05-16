#include <memory>
#include <images/module.h>
#include <system/environment.h>
#include "material.h"
#include "texture_slot.h"

PUNK_ENGINE_BEGIN
namespace Attributes
{
    TextureSlot::TextureSlot()
    {}

	TextureSlot::~TextureSlot() {

	}

    void TextureSlot::SetScale(const Math::vec3& value) {
        m_scale = value;
    }

    const Math::vec3& TextureSlot::GetScale() const {
        return m_scale;
    }

    void TextureSlot::SetFilename(const Core::String& value) {
        m_image_filename = value;
    }

    const Core::String& TextureSlot::GetFilename() const {
        return m_image_filename;
    }

    void TextureSlot::SetFactor(float value) {
        m_factor = value;
    }

    float TextureSlot::GetFactor() const {
        return m_factor;
    }
}
PUNK_ENGINE_END
