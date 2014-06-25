#include <memory>
#include <system/factory/module.h>
#include <images/module.h>
#include <system/logger/module.h>
#include <system/environment.h>
#include "material.h"
#include "texture_slot.h"

PUNK_ENGINE_BEGIN
namespace Attributes
{
    TextureSlot::TextureSlot()
    {}

	TextureSlot::~TextureSlot() {
		System::GetDefaultLogger()->Debug("TextureSlot destroyed");
	}

	void TextureSlot::QueryInterface(const Core::Guid& type, void** object) {
		if (!object)
			return;

		if (type == Core::IID_IObject) {
			*object = (Core::IObject*)(IDiffuseTextureSlot*)object;
			AddRef();
		}
		else if (type == IID_ITextureSlot) {
			*object = (ITextureSlot*)(IDiffuseTextureSlot*)object;
			AddRef();
		}
		else if (type == IID_IDiffuseTextureSlot) {
			*object = (IDiffuseTextureSlot*)object;
			AddRef();
		}
		else if (type == IID_INormalTextureSlot) {
			*object = (INormalTextureSlot*)object;
			AddRef();
		}
		else if (type == IID_ISpecularIntensityTextureSlot) {
			*object = (ISpecularIntensityTextureSlot*)object;
			AddRef();
		}
		else
			*object = nullptr;
	}

	std::uint32_t TextureSlot::AddRef() {
		return m_ref_count.fetch_add(1);
	}

	std::uint32_t TextureSlot::Release() {
		auto v = m_ref_count.fetch_sub(1) - 1;
		if (!v) {
			delete this;
		}
		return v;
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

	void TextureSlot::SetTexture(Graphics::ITexture2D* value) {
		value->AddRef();
		m_texture_2d.reset(value);
	}

	Graphics::ITexture2D* TextureSlot::GetTexture() {
		return m_texture_2d.get();
	}

	PUNK_REGISTER_CREATOR(IID_IDiffuseTextureSlot, (System::CreateInstance<TextureSlot, IDiffuseTextureSlot>));
	PUNK_REGISTER_CREATOR(IID_INormalTextureSlot, (System::CreateInstance<TextureSlot, INormalTextureSlot>));
	PUNK_REGISTER_CREATOR(IID_ISpecularIntensityTextureSlot, (System::CreateInstance<TextureSlot, ISpecularIntensityTextureSlot>));
}
PUNK_ENGINE_END
