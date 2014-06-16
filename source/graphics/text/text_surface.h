#ifndef _H_PUNK_TEXT_TEXTURE
#define _H_PUNK_TEXT_TEXTURE

#include <string/module.h>
#include <graphics/texture/module.h>
#include "itext_surface.h"

PUNK_ENGINE_BEGIN
namespace Graphics
{
    class ITexture2D;
    class IVideoDriver;

    class PUNK_ENGINE_LOCAL TextSurface : public ITextSurface
    {
    public:

        TextSurface(IVideoDriver* driver);
        TextSurface(std::uint32_t width, std::uint32_t height, IVideoDriver* driver);
        virtual ~TextSurface();

        void SetSize(std::uint32_t width, std::uint32_t height) override;
        void SetAutoWrapFlag(bool value) override { m_auto_wrap = value; }
        bool GetAutoWrapFlag() const override { return m_auto_wrap; }
        void SetAutoFitSizeFlag(bool value) override { m_auto_fit_size = value; }
        bool GetAutoFitSizeFlag() const override { return m_auto_fit_size; }
        void SetText(const Core::String& text) override;
        const Core::String& GetText() const override;
        ITexture2D* GetTexture() override;
        virtual void SetFont(Font::IFont* font) override;
        virtual const Font::IFont* GetFont() const override;
        void SetHorizontalAlignment(TextHorizontalAlignment value) override { m_halignment = value; RenderTextToTexture(); }
        TextHorizontalAlignment GetHorizontalAlignment() const override { return m_halignment; }
        void SetVerticalAlignment(TextVerticalAlignment value) override { m_valignment = value; RenderTextToTexture(); }
        TextVerticalAlignment GetVerticalAlignment() const override { return m_valignment; }

    private:
        int CalculateTextXOffset(const Core::String& text);
        int CalculateTextYOffset(const Core::String& text);
        bool RenderTextToTexture();
        void UpdateTextureSize();

    private:
        TextHorizontalAlignment m_halignment {TextHorizontalAlignment::Left};
        TextVerticalAlignment m_valignment {TextVerticalAlignment::Top};
        bool m_auto_wrap {false};
        bool m_auto_fit_size {false};
        bool m_need_update {true};
        Core::String m_text;
        Font::IFont* m_font {nullptr};

        // should be destroyed in destructor
        ITexture2DUniquePtr m_texture {nullptr, Core::DestroyObject};
        IVideoDriver* m_video_driver {nullptr};
    };
}
PUNK_ENGINE_END

#endif // _H_PUNK_TEXT_TEXTURE
