#ifndef TEXTURE_H
#define TEXTURE_H

#include <cstdint>
#include "texture_filter.h"
#include "texture_wrap.h"
#include "texture_compare_func.h"
#include "texture_compare_mode.h"

PUNK_ENGINE_BEGIN
namespace Graphics
{
    class IVideoDriver;

    class ITexture
    {
    public:
        virtual bool IsValid() const = 0;
        virtual std::uint32_t GetMemoryUsage() const = 0;
        virtual void SetMinFilter(TextureFilter value) = 0;
        virtual void SetMagFilter(TextureFilter value) = 0;
        virtual void SetWrapMode(TextureWrapDirection dir, TextureWrapMode mode) = 0;
        virtual void SetCompareFunction(TextureCompareFunc value) = 0;
        virtual void SetCompareMode(TextureCompareMode value) = 0;
        virtual void Bind() = 0;
        virtual void Bind(std::int32_t slot) = 0;
        virtual void Unbind() = 0;
        virtual IVideoDriver* GetVideoDriver() = 0;
    };
}
PUNK_ENGINE_END

#endif // TEXTURE_H
