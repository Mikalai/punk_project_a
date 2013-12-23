#include "widget_render.h"
#include "font_manager.h"
#include "../widgets/module.h"
#include "render.h"
#include "style.h"

namespace Gui
{
    void WidgetRender::Render(Widget* w)
    {
        m_render->PushSate();
        if (w->GetBackColor().a > 0.0f)
        {
            m_render->SetColor(w->GetBackColor());
            m_render->SetAlpha(w->GetBackColor().a);
            m_render->DrawQuad(w->GetLocalX(), w->GetLocalY(), w->GetWidth(), w->GetHeight());
        }
        m_render->PopState();
    }

    void WidgetRender::Render(Button* w)
    {
        m_render->PushSate();
        m_render->Translate(w->GetLocalX(), w->GetLocalY());
        if (w->GetBackColor().a > 0.0f)
        {
            m_render->SetColor(w->GetBackColor());
            m_render->SetAlpha(w->GetBackColor().a);
            if (w->GetStyle()->IsEnabledTextures())
            {
                m_render->SetTexture(w->GetBackTexture());
                m_render->DrawTexturedQuad(0, 0, w->GetWidth(), w->GetHeight());
            }
            else
            {
                m_render->DrawQuad(0, 0, w->GetWidth(), w->GetHeight());
            }
            m_render->SetColor(0, 0, 0);
            m_render->SetAlpha(w->GetBackColor().a);

            float text_height = m_render->GetFontManager()->GetCharacterHeight('I');
            size_t symbols = 0;
            float offset = w->Checked() ? -10.0f : 1.0f;	//	TODO: add this in xml scheme
            float text_width = 0;
            while (text_width < w->GetWidth() && symbols < w->GetText().size())
            {
                symbols++;
                float width = m_render->GetFontManager()->GetCharacterWidth(w->GetText()[symbols]);
                if (width + text_width + offset > w->GetWidth()-offset)
                    break;
                text_width += width;
            }
            if (symbols)
            {
                float y_offset = w->Checked() ? 4.0f : 0.0f;	//	TODO: add this in xml scheme
                m_render->DrawTextLine(offset + (w->GetWidth() - text_width) / 2.0f, (w->GetHeight() - text_height) / 2.0f + y_offset, w->GetText().substr(0, symbols));
            }
        }
        m_render->PopState();
    }

    void WidgetRender::Render(ContainerWidget* w)
    {
        m_render->PushSate();
        if (w->GetBackColor().a > 0.0f)
        {
            m_render->SetColor(w->GetBackColor());
            m_render->SetAlpha(w->GetBackColor().a);
            if (w->GetStyle()->IsEnabledTextures())
            {
                m_render->SetTexture(w->GetBackTexture());
                m_render->DrawTexturedQuad(w->GetLocalX(), w->GetLocalY(), w->GetWidth(), w->GetHeight());
            }
            else
            {
                m_render->DrawQuad(w->GetLocalX(), w->GetLocalY(), w->GetWidth(), w->GetHeight());
            }
        }

        m_render->Translate(w->GetLocalX(), w->GetLocalY());
        for (ContainerWidget::ChildrenCollection::iterator it = w->GetChildren().begin(); it != w->GetChildren().end(); ++it)
        {
            WidgetPtr child = (*it).second;
            child->Repaint(this);
        }
        m_render->PopState();
    }

    void WidgetRender::Render(Image *w)
    {
        m_render->PushSate();
        if (w->GetBackColor().a > 0.0f)
        {
            m_render->Translate(w->GetLocalX(), w->GetLocalY());
            if (w->GetBackColor().a > 0.0f)
            {
                m_render->SetColor(w->GetBackColor());
                m_render->SetAlpha(w->GetBackColor().a);
                if (w->GetContent().get())
                {
                    m_render->SetTexture(w->GetContent());
                    m_render->DrawTexturedQuad(0, 0, w->GetWidth(), w->GetHeight());
                }
                else
                {
                    if (w->GetStyle()->IsEnabledTextures())
                    {
                        m_render->SetTexture(w->GetBackTexture());
                        m_render->DrawTexturedQuad(0, 0, w->GetWidth(), w->GetHeight());
                    }
                    else
                    {
                        m_render->DrawQuad(0, 0, w->GetWidth(), w->GetHeight());
                    }
                }
            }
            m_render->PopState();
        }
    }

    void WidgetRender::SetRender(boost::shared_ptr<AbstractRender> value)
    {
        m_render = value;
    }
}
