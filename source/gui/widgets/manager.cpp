#include <sstream>
#include <stdio.h>
#include <stdexcept>
#include <string.h>
#include <expat.h>
#include <iostream>
#include <algorithm>
#include "container_widget.h"
#include "../common/font_manager.h"
#include "../common/widget_render.h"
#include "../common/render.h"
#include "../common/input_device.h"
#include "../common/action.h"
#include "../common/style.h"
#include "../common/picture.h"
#include "manager.h"
#include "button.h"
#include "image.h"
#include "widget.h"

namespace Gui
{	
    boost::scoped_ptr<Manager> Manager::m_instance;

    struct ManagerImpl : public ContainerWidget
    {
    public:

        float m_viewport_left;
        float m_viewport_top;
        float m_viewport_height;
        float m_viewport_width;

        float m_prev_x;
        float m_prev_y;
        float m_x;
        float m_y;
        bool m_left_down;
        bool m_right_down;
        bool m_middle_down;
        boost::shared_ptr<AbstractRender> m_render;
        boost::shared_ptr<AbstractFontManager> m_font;
        boost::shared_ptr<AbstractInputDevice> m_input_device;
        boost::shared_ptr<AbstractPictureFactory> m_picture_factory;
        WidgetPtr m_cursor_widget;
        WidgetPtr m_focus;
        std::map<const std::string, boost::shared_ptr<StyleSet> > m_styles;

        void SetMouseCursorPosition(float x, float y)
        {
            m_prev_x = x;
            m_prev_y = y;
            m_x = x - m_viewport_left;
            m_y = y - m_viewport_top;
        }

        boost::shared_ptr<StyleSet> GetStyleSet(const std::string& name)
        {
            std::map<const std::string, boost::shared_ptr<StyleSet> >::iterator it = m_styles.find(name);
            if (it == m_styles.end())
                throw std::runtime_error("Style " + name + " was not loaded");
            return it->second;
        }

        void LoadStyleSet(const std::string& filename)
        {
            boost::shared_ptr<StyleSet> style_set = StyleSet::Create(filename, m_picture_factory);
            if (!style_set.get())
                return;
            m_styles[style_set->GetName()] = style_set;
        }

        void Render()
        {
            WidgetRender widget_render;
            widget_render.SetRender(m_render);

            m_render->PushSate();
            m_render->Translate(m_viewport_left, m_viewport_top);
            for (ChildrenCollection::iterator it = GetChildren().begin(); it != GetChildren().end(); ++it)
            {
                m_render->PushSate();
                WidgetPtr w = (*it).second;
                if (w->IsVisible())
                {
                    w->Repaint(&widget_render);
                }
                m_render->PopState();
            }
            m_render->SetColor(1, 1, 1);
            m_render->PopState();

	
			if (m_cursor_widget.get() && m_cursor_widget->GetStyle().get() && m_cursor_widget->GetStyle()->GetCursor().get())
			{
				m_render->SetTexture(m_cursor_widget->GetStyle()->GetCursor());
				m_render->DrawTexturedQuad(m_x, m_y, -1, -1);
			}
			else if (GetStyle().get() && GetStyle()->GetCursor().get())
			{
				m_render->SetTexture(GetStyle()->GetCursor());
				m_render->DrawTexturedQuad(m_x, m_y, -1, -1);
			}
			else 
			{
				m_render->DrawQuad(m_x, m_y, 5, 5);
			}
        }
        
        float GetWindowWidth()
        {
            return m_viewport_width;
        }
        
        float GetWindowHeight()
        {
            return m_viewport_height;
        }

        void SetViewport(float left, float top, float width, float height)
        {
            m_viewport_left = left;
            m_viewport_top = top;
            m_viewport_width = width;
            m_viewport_height = height;
        }

        void SetPictureFactory(boost::shared_ptr<AbstractPictureFactory> factory)
        {
            m_picture_factory = factory;
        }

        boost::shared_ptr<AbstractPictureFactory> GetPictureFactory()
        {
            return m_picture_factory;
        }

        void SetRender(boost::shared_ptr<AbstractRender> render)
        {
            m_render = render;
        }

        boost::shared_ptr<AbstractRender> GetRender()
        {
            return m_render;
        }

        void SetFontManager(boost::shared_ptr<AbstractFontManager> font)
        {
            m_font = font;
        }

        void SetInputDevice(boost::shared_ptr<AbstractInputDevice> device)
        {
            m_input_device = device;
        }

        boost::shared_ptr<AbstractInputDevice> GetInputDevice()
        {
            return m_input_device;
        }

        boost::shared_ptr<AbstractFontManager> GetFontManager()
        {
            return m_font;
        }

        ManagerImpl()
            : ContainerWidget(0, 0, 0, 0, 0, "")
        {
            m_prev_x = 0;
            m_prev_y = 0;
            m_x = 0;
            m_y = 0;
            m_left_down = false;
            m_right_down = false;
            m_middle_down = false;
            m_viewport_left = 0;
            m_viewport_top = 0;
            m_viewport_height = 0;
            m_viewport_width = 0;
        }

        virtual ~ManagerImpl()
        {
        }

        virtual void OnMouseMove(float x, float y, int button)
        {
            m_prev_x = m_x;
            m_prev_y = m_y;
            m_x = x;
            m_y = y;

            if (m_left_down)
            {
                if (m_focus && m_focus->IsMoveable())
                {
                    m_focus->SetLocalPosition(m_focus->GetLocalX() + (m_x - m_prev_x), m_focus->GetLocalY() + m_y - m_prev_y);
                }
            }

            WidgetPtr new_widget = GetWidget(m_x, m_y);
            if (m_cursor_widget != new_widget)
            {
                if (m_cursor_widget)
                    m_cursor_widget->MouseLeave(x, y);
                if (new_widget)
                    new_widget->MouseEnter(x, y);
                m_cursor_widget = new_widget;
            }

            if (m_cursor_widget)
            {
                m_cursor_widget->MouseMove(x, y, button);
            }
        }

        virtual void OnMousePress(float x, float y, int button)
        {
            m_left_down = (button == LeftButton ? true : m_left_down);
            m_right_down = (button == RightButton ? true : m_right_down);
            m_middle_down = (button == MiddleButton ? true : m_middle_down);

            WidgetPtr new_focus = GetWidget(x, y);
            if (new_focus != m_focus)
            {
                if (m_focus)
                    m_focus->Unfocus();
                if (new_focus)
                    new_focus->Focus();
                m_focus = new_focus;
            }

            if (m_focus)
            {
                WidgetPtr parent = m_focus;
                while (parent->Parent().lock().get())
                    parent = parent->Parent().lock();
                //MoveToFront(parent);
            }

            if (m_cursor_widget)
            {
                m_cursor_widget->MousePress(x, y, button);
            }
        }

        void OnMouseRelease(float x, float y, int button)
        {
            m_left_down = (button == LeftButton ? false : m_left_down);
            m_right_down = (button == RightButton ? false : m_right_down);
            m_middle_down = (button == MiddleButton ? false : m_middle_down);

            WidgetPtr w = GetWidget(x, y);

            if (w && w == m_focus)
            {
                w->MouseClicked(x, y, button);
            }

            if (m_cursor_widget)
            {
                m_cursor_widget->MouseRelease(x, y, button);
            }
        }
    };


    Manager::Manager()
        : impl(new ManagerImpl())
    {
    }

    Manager::~Manager()
    {
        impl.reset();
    }

    void Manager::MouseMove(float x, float y, int button)
    {
        impl->MouseMove(x, y, button);
    };

    void Manager::MousePress(float x, float y, int button)
    {
        impl->MousePress(x, y, button);
    }

    void Manager::MouseRelease(float x, float y, int button)
    {
        impl->MouseRelease(x, y, button);
    }

    float Manager::GetWindowWidth()
    {
        return impl->GetWindowWidth();
    }

    float Manager::GetWindowHeight()
    {
        return impl->GetWindowHeight();
    }

    boost::shared_ptr<AbstractFontManager> Manager::GetFontManager()
    {
        return impl->GetFontManager();
    }

    boost::scoped_ptr<Manager>& Manager::Instance()
    {
        if (!m_instance.get())
            m_instance.reset(new Manager());
        return m_instance;
    }

    void Manager::Destroy()
    {
        m_instance.reset(0);
    }

    void Manager::AddWidget(boost::shared_ptr<ContainerWidget> value)
    {
        impl->AddWidget(value);
    }

    void Manager::RemoveWidget(boost::shared_ptr<ContainerWidget> value)
    {
        impl->RemoveWidget(value);
    }

    void Manager::SetRender(boost::shared_ptr<AbstractRender> render)
    {
        impl->SetRender(render);
    }

    boost::shared_ptr<AbstractRender> Manager::GetRender()
    {
        return impl->GetRender();
    }

    void Manager::SetFontManager(boost::shared_ptr<AbstractFontManager> font)
    {
        impl->SetFontManager(font);
    }

    void Manager::SetInputDevice(boost::shared_ptr<AbstractInputDevice> device)
    {
        impl->SetInputDevice(device);
    }

    void Manager::Render()
    {
        impl->Render();
    }

    void Manager::SetViewport(float left, float top, float width, float height)
    {
        impl->SetViewport(left, top, width, height);
    }

    void Manager::Update(float dt)
    {
    }

    void Manager::SetPictureFactory(boost::shared_ptr<AbstractPictureFactory> value)
    {
        impl->SetPictureFactory(value);
    }

    boost::shared_ptr<AbstractPictureFactory> Manager::GetPictureFactory()
    {
        return impl->GetPictureFactory();
    }

    boost::shared_ptr<StyleSet> Manager::GetStyleSet(const std::string &name)
    {
        return impl->GetStyleSet(name);
    }

    void Manager::LoadStyleSet(const std::string &filename)
    {
        impl->LoadStyleSet(filename);
    }

    WidgetPtr Manager::FindByName(const std::string &name)
    {
        return impl->FindChildByName(name);
    }

    struct Buffer2
    {
        Manager* manager;
        boost::shared_ptr<ContainerWidget> container;
        boost::shared_ptr<Button> button;
        boost::shared_ptr<Image> image;
    };

    void gui_start(void *data, const char *el, const char **attr)
    {
        Buffer2* d = (Buffer2*)data;
        int i;

        if (!strcmp(el, "container_widget"))
        {
            std::string name, style;
            float x, y, width, height;
            int order;
            bool visible, moveable, fixed;
            for (i = 0; attr[i]; i += 2)
            {
                if (!strcmp(attr[i], "name"))
                    name.assign(attr[i+1]);
                else if (!strcmp(attr[i], "x"))
                    x = (float)atof(attr[i+1]);
                else if (!strcmp(attr[i], "y"))
                    y = (float)atof(attr[i+1]);
                else if (!strcmp(attr[i], "width"))
                    width = (float)atof(attr[i+1]);
                else if (!strcmp(attr[i], "height"))
                    height = (float)atof(attr[i+1]);
                else if (!strcmp(attr[i], "visible"))
                    visible = atoi(attr[i+1]) != 0;
                else if (!strcmp(attr[i], "moveable"))
                    moveable = atoi(attr[i+1]) != 0;
                else if (!strcmp(attr[i], "fixed"))
                    fixed = atoi(attr[i+1]) != 0;
                else if (!strcmp(attr[i], "order"))
                    order = atoi(attr[i+1]);
                else if (!strcmp(attr[i], "style"))
                    style = attr[i+1];
            }
            d->container.reset(new ContainerWidget(x, y, width, height, order, name));
            d->container->SetFixed(fixed);
            d->container->SetMoveable(moveable);
            d->container->SetVisible(visible);
            d->container->SetStyle(d->manager->GetStyleSet(style)->GetStyle("container_widget"));
        }
        else if (!strcmp(el, "button"))
        {
            std::string name, style, text;
            float x, y, width, height;
            int order;
            bool visible, moveable, fixed;
            for (i = 0; attr[i]; i += 2)
            {
                if (!strcmp(attr[i], "name"))
                    name = attr[i+1];
                else if (!strcmp(attr[i], "x"))
                    x = (float)atof(attr[i+1]);
                else if (!strcmp(attr[i], "y"))
                    y = (float)atof(attr[i+1]);
                else if (!strcmp(attr[i], "width"))
                    width = (float)atof(attr[i+1]);
                else if (!strcmp(attr[i], "height"))
                    height = (float)atof(attr[i+1]);
                else if (!strcmp(attr[i], "style"))
                    style = attr[i+1];
                else if (!strcmp(attr[i], "visible"))
                    visible = atoi(attr[i+1]) != 0;
                else if (!strcmp(attr[i], "moveable"))
                    moveable = atoi(attr[i+1]) != 0;
                else if (!strcmp(attr[i], "fixed"))
                    fixed = atoi(attr[i+1]) != 0;
                else if (!strcmp(attr[i], "order"))
                    order = atoi(attr[i+1]);
                else if (!strcmp(attr[i], "text"))
                    text = attr[i+1];
            }
            d->button.reset(new Button(x, y, width, height, order, text, name));
            d->button->SetFixed(fixed);
            d->button->SetMoveable(moveable);
            d->button->SetVisible(visible);
            d->button->SetStyle(d->manager->GetStyleSet(style)->GetStyle("button"));
        }
        else if (!strcmp(el, "image"))
        {
            std::string name, style;
            float x, y, width, height;
            int order;
            bool visible, moveable, fixed;
            for (i = 0; attr[i]; i += 2)
            {
                if (!strcmp(attr[i], "name"))
                    name = attr[i+1];
                else if (!strcmp(attr[i], "x"))
                    x = (float)atof(attr[i+1]);
                else if (!strcmp(attr[i], "y"))
                    y = (float)atof(attr[i+1]);
                else if (!strcmp(attr[i], "width"))
                    width = (float)atof(attr[i+1]);
                else if (!strcmp(attr[i], "height"))
                    height = (float)atof(attr[i+1]);
                else if (!strcmp(attr[i], "style"))
                    style = attr[i+1];
                else if (!strcmp(attr[i], "visible"))
                    visible = atoi(attr[i+1]) != 0;
                else if (!strcmp(attr[i], "moveable"))
                    moveable = atoi(attr[i+1]) != 0;
                else if (!strcmp(attr[i], "fixed"))
                    fixed = atoi(attr[i+1]) != 0;
                else if (!strcmp(attr[i], "order"))
                    order = atoi(attr[i+1]);
            }
            d->image.reset(new Image(x, y, width, height, order, name));
            d->image->SetFixed(fixed);
            d->image->SetMoveable(moveable);
            d->image->SetVisible(visible);
            d->image->SetStyle(d->manager->GetStyleSet(style)->GetStyle("image"));
        }
        else if (!strcmp(el, "image_set_content"))
        {
            std::string file;
            float x, y, width, height;
            for (i = 0; attr[i]; i += 2)
            {
                if (!strcmp(attr[i], "file"))
                    file = attr[i+1];
                else if (!strcmp(attr[i], "x"))
                    x = (float)atof(attr[i+1]);
                else if (!strcmp(attr[i], "y"))
                    y = (float)atof(attr[i+1]);
                else if (!strcmp(attr[i], "width"))
                    width = (float)atof(attr[i+1]);
                else if (!strcmp(attr[i], "height"))
                    height = (float)atof(attr[i+1]);
            }
            if (!d->image.get())
                throw std::runtime_error("Can't set cotent, because image was not created");
            d->image->SetContent(d->manager->GetPictureFactory()->Create(file, x, y, width, height));
        }
    }

    void gui_end(void *data, const char *el)
    {
        Buffer2* d = (Buffer2*)data;

        if (!strcmp(el, "button"))
        {
            Gui::Attach(d->button, d->container);
            d->button.reset();
        }
        else if (!strcmp(el, "image"))
        {
            Gui::Attach(d->image, d->container);
            d->image.reset();
        }
        else if (!strcmp(el, "container_widget"))
        {
            d->manager->AddWidget(d->container);
            d->container.reset();
        }
    }

    void Manager::LoadFromFile(const std::string& filename)
    {
        XML_Parser p = XML_ParserCreate(NULL);
        if (! p)
            throw std::runtime_error("Couldn't allocate memory for parser");

        XML_SetElementHandler(p, gui_start, gui_end);
        Buffer2 b;
        b.manager = this;        
        XML_SetUserData(p, &b);

#if _MSC_VER >= 1500
        FILE* f = 0;
		fopen_s(&f, filename.c_str(), "rb");
#else
		FILE* f = fopen(filename.c_str(), "rb");
#endif
        if (f == 0)
            throw std::runtime_error("Can't open file " + filename);

        fseek(f, 0, SEEK_END);
        int size = ftell(f);
        fseek(f, 0, SEEK_SET);
        std::vector<char> buffer;
        buffer.resize(size);
        fread(&buffer[0], sizeof(char), size, f);

        try
        {
            if (!XML_Parse(p, &buffer[0], buffer.size(), 1))
            {
                std::stringstream stream;
                stream << "Parse error at line " << XML_GetCurrentLineNumber(p) << ":\n" << XML_ErrorString(XML_GetErrorCode(p));
                std::cerr << stream.str() << std::endl;
                throw std::runtime_error(stream.str());
            }
        }
        catch(...)
        {
            fclose(f);
            XML_ParserFree(p);
            throw;
        }
        fclose(f);
        XML_ParserFree(p);
    }
}
