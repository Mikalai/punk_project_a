#include <system/concurrency/module.h>
#include <graphics/video_driver/module.h>
#include <graphics/texture/module.h>
#include <fonts/module.h>
#include "text_surface.h"

PUNK_ENGINE_BEGIN
namespace Graphics {
    TextSurface::TextSurface(IVideoDriver *driver)
        : m_video_driver(driver)
        , m_need_update(true)
        , m_texture(nullptr, DestroyTexture2D)
        , m_halignment(TextHorizontalAlignment::Left)
        , m_valignment(TextVerticalAlignment::Top)
        , m_font(nullptr)
        , m_auto_wrap(false)
        , m_auto_fit_size(true) {}

    TextSurface::TextSurface(std::uint32_t width, std::uint32_t height, IVideoDriver *driver)
        : m_video_driver(driver)
        , m_need_update(false) {
        m_texture = CreateTexture2D(width, height, ImageModule::ImageFormat::RED, nullptr, false, m_video_driver);
        m_halignment = TextHorizontalAlignment::Left;
        m_valignment = TextVerticalAlignment::Top;        
        m_auto_wrap = false;
        m_auto_fit_size = true;
    }

    TextSurface::~TextSurface() {
        m_texture.reset(nullptr);
    }

    void TextSurface::SetSize(std::uint32_t width, std::uint32_t height)
    {
        if (!m_texture)
            m_texture = CreateTexture2D(width, height, ImageModule::ImageFormat::RED, 0, false, m_video_driver);
        else
            m_texture->Resize(width, height);
    }

    int TextSurface::CalculateTextXOffset(const Core::String& text)
    {
        if (!m_font)
            return 0;

        int start_x;
        if (TextHorizontalAlignment::Left == m_halignment)
            start_x = 0;
        else if (TextHorizontalAlignment::Center == m_halignment)
        {
            std::uint32_t length = m_font->CalculateLength(text);
            if (length >= m_texture->GetWidth())
                start_x = 0;
            else
                start_x = (m_texture->GetWidth() - length) / 2;
        }
        else if (TextHorizontalAlignment::Right == m_halignment)
        {
            std::uint32_t length = m_font->CalculateLength(text);
            if (length >= m_texture->GetWidth())
                start_x = 0;
            else
                start_x = m_texture->GetWidth() - length;
        }
        return start_x;
    }

    int TextSurface::CalculateTextYOffset(const Core::String& text)
    {        
        if (!m_font)
            return 0;

        int length = m_font->CalculateLength(m_text);
        if (length == 0)
            return 1;

        int max_offset = m_font->GetMaxOffset(text);
        int min_offset = m_font->GetMinOffset(text);
        int max_height = max_offset - min_offset;
        //int max_lines = m_texture->GetHeight() / max_height;
        int req_lines = length / m_texture->GetWidth();
        int start_y = 0;
        if (TextVerticalAlignment::Bottom == m_valignment)
        {
            start_y = 0;
        }
        else if (TextVerticalAlignment::Center == m_valignment)
        {
            start_y = m_texture->GetHeight() / 2 + req_lines*max_height / 2;
        }
        else if (TextVerticalAlignment::Top == m_valignment)
        {
            start_y = max_offset;
        }
        return start_y;
    }

    bool TextSurface::RenderTextToTexture()
    {
        if (!m_font)
            return false;
        UpdateTextureSize();

        if (!m_texture)
            return false;

        m_texture->Fill(0);

        if (m_text.Length() == 0)
            if (m_texture)
                return true;        

        int start_x, start_y;
        int x = start_x = CalculateTextXOffset(m_text);
        int y = start_y = CalculateTextYOffset(m_text);

        for (size_t i = 0; i != m_text.Length(); ++i)
        {
            wchar_t* a = &m_text[i];
            int width;
            int height;
            int x_offset;
            int y_offset;
            int x_advance;
            int y_advance;
            unsigned char* buffer;
            m_font->RenderChar(*a, &width, &height, &x_offset, &y_offset, &x_advance, &y_advance, &buffer);
            if (x_offset < 0 && x == 0)
                x += -x_offset;
            if (x + x_offset + width >= m_texture->GetWidth())
            {
                y -= m_font->GetHeight(L'M');
                x = CalculateTextXOffset(a);
                if (y < 0)
                    return true;
            }
            m_texture->CopyFromCpu(x + x_offset, y - y_offset, width, height, buffer);
            x += x_advance;
        }
        return true;
    }

    void TextSurface::SetFont(Font::IFont* font)
    {
        m_font = font;
        m_need_update = true;
    }    

    const Font::IFont* TextSurface::GetFont() const {
        return m_font;
    }

    void TextSurface::SetText(const Core::String& text)
    {
        m_text = text;
        m_need_update = true;
    }

    void TextSurface::UpdateTextureSize()
    {
        if (!m_font)
            return;

        if (GetAutoFitSizeFlag())
        {
            auto width = m_font->CalculateLength(m_text);
            auto height = m_font->CalculateHeight(m_text);
            if (m_texture)
                m_texture->Resize(width, height);
            else
                m_texture = CreateTexture2D(width, height, ImageModule::ImageFormat::RED, nullptr, false, m_video_driver);
        }
    }

    const Core::String& TextSurface::GetText() const
    {
        return m_text;
    }

    ITexture2D* TextSurface::GetTexture()
    {
        if (m_need_update)
            RenderTextToTexture();
        return m_texture.get();
    }

    extern PUNK_ENGINE_API ITextSurfaceUniquePtr CreateTextSurface(std::uint32_t width, std::uint32_t height, IVideoDriver* driver) {
        ITextSurfaceUniquePtr ptr{nullptr, DestroyTextSurface};
        if (width == 0 || height == 0)
            ptr.reset(new TextSurface{driver});
        else
            ptr.reset(new TextSurface{width, height, driver});
        return ptr;
    }

    extern PUNK_ENGINE_API void DestroyTextSurface(ITextSurface* value) {
        TextSurface* o = dynamic_cast<TextSurface*>(value);
        delete o;
    }
}
PUNK_ENGINE_END
