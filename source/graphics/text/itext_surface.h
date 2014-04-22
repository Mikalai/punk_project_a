#ifndef ITEXT_SURFACE_H
#define ITEXT_SURFACE_H

#include <memory>
#include <config.h>
#include <cstdint>
#include "text_horizontal_alignment.h"
#include "text_vertical_alignment.h"
#include "text_direction.h"

PUNK_ENGINE_BEGIN
namespace Font { class IFont; }
namespace Graphics {

    class ITexture2D;
    class IVideoDriver;

    class ITextSurface {
    public:
        virtual void SetSize(std::uint32_t width, std::uint32_t height) = 0;
        virtual void SetAutoWrapFlag(bool value) = 0;
        virtual bool GetAutoWrapFlag() const = 0;
        virtual void SetAutoFitSizeFlag(bool value) = 0;
        virtual bool GetAutoFitSizeFlag() const = 0;
        virtual void SetText(const Core::String& text) = 0;
        virtual const Core::String& GetText() const = 0;
        virtual ITexture2D* GetTexture() = 0;
        virtual void SetFont(Font::IFont* font) = 0;
        virtual const Font::IFont* GetFont() const = 0;
        virtual void SetHorizontalAlignment(TextHorizontalAlignment value) = 0;
        virtual TextHorizontalAlignment GetHorizontalAlignment() const = 0;
        virtual void SetVerticalAlignment(TextVerticalAlignment value) = 0;
        virtual TextVerticalAlignment GetVerticalAlignment() const = 0;
    };

    using ITextSurfaceUniquePtr = std::unique_ptr<ITextSurface, void (*)(ITextSurface*)>;

    extern PUNK_ENGINE_API ITextSurfaceUniquePtr CreateTextSurface(std::uint32_t width, std::uint32_t height, IVideoDriver* driver);
    extern PUNK_ENGINE_API void DestroyTextSurface(ITextSurface* value);
}
PUNK_ENGINE_END

#endif // ITEXT_SURFACE_H
