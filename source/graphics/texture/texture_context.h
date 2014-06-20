#ifndef _H_PUNK_TEXTURE_CONTEXT
#define _H_PUNK_TEXTURE_CONTEXT

#include <config.h>
#include <core/poolable.h>

#include <memory>

PUNK_ENGINE_BEGIN
namespace Graphics
{
    class ITexture;

    class PUNK_ENGINE_LOCAL TextureContext : public Core::Poolable<TextureContext>
    {
    public:
        TextureContext();
        ~TextureContext();

        void SetTexture(int slot, ITexture* map);
        void Clear();

        void Bind();
        void Unbind();
    private:
        static const int MAX_TEXTURES = 32;
        //	this pointers should not be deleted in destructor
        ITexture* m_textures[MAX_TEXTURES];
    private:
        TextureContext(const TextureContext& tc);
        TextureContext& operator = (const TextureContext& tc);
    };
}
PUNK_ENGINE_END

#endif
