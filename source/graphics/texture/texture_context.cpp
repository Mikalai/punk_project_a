#include <memory.h>
#include "texture_context.h"
#include "itexture.h"

PUNK_ENGINE_BEGIN
namespace Graphics {

    TextureContext::TextureContext()
    {
        memset(m_textures, 0, sizeof(m_textures));
    }

    TextureContext::~TextureContext()
    {

    }

    void TextureContext::Clear()
    {
        memset(m_textures, 0, sizeof(m_textures));
    }

    void TextureContext::Bind()
    {
        for (int i = 0; i < MAX_TEXTURES; ++i)
        {
            if (m_textures[i])
            {
                m_textures[i]->Bind(i);
            }
        }
    }

    void TextureContext::Unbind()
    {
        for (int i = 0; i < MAX_TEXTURES; ++i)
        {
            if (m_textures[i])
            {
                m_textures[i]->Unbind();
                m_textures[i] = nullptr;
            }
        }
    }

    void TextureContext::SetTexture(int slot, ITexture* map)
    {
        m_textures[slot] = map;
    }

}
PUNK_ENGINE_END

