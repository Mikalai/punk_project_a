#include <sstream>
#include <stdio.h>
#include <stdexcept>
#include <vector>
#include <string.h>
#include "picture.h"
#include "style.h"
#include <expat.h>

namespace Gui
{
    struct Buffer
    {
        boost::shared_ptr<Style> style;
        boost::shared_ptr<StyleSet> style_set;
        boost::shared_ptr<AbstractPictureFactory> factory;
    };

    Style::Style()
    {
        m_back_color[BACK_COLOR].r = 0.6f;
        m_back_color[BACK_COLOR].g = 0.6f;
        m_back_color[BACK_COLOR].b = 0.6f;
        m_back_color[BACK_COLOR].a = 0.4f;

        m_back_color[BACK_COLOR_FOCUSED].r = 0.6f;
        m_back_color[BACK_COLOR_FOCUSED].g = 0.6f;
        m_back_color[BACK_COLOR_FOCUSED].b = 0.6f;
        m_back_color[BACK_COLOR_FOCUSED].a = 0.9f;

        m_back_color[BACK_COLOR_MOUSE_OVER].r = 0.6f;
        m_back_color[BACK_COLOR_MOUSE_OVER].g = 0.6f;
        m_back_color[BACK_COLOR_MOUSE_OVER].b = 0.6f;
        m_back_color[BACK_COLOR_MOUSE_OVER].a = 0.5f;

        m_back_color[BACK_COLOR_MOUSE_PRESSED].r = 0.3f;
        m_back_color[BACK_COLOR_MOUSE_PRESSED].g = 0.3f;
        m_back_color[BACK_COLOR_MOUSE_PRESSED].b = 0.3f;
        m_back_color[BACK_COLOR_MOUSE_PRESSED].a = 1.0f;
    }

    Style::~Style()
    {}

    StyleSet::~StyleSet()
    {}

    void start(void *data, const char *el, const char **attr)
    {
        Buffer* d = (Buffer*)data;
        int i;

        if (!strcmp(el, "style"))
        {
            d->style_set.reset(new StyleSet);
            for (i = 0; attr[i]; i += 2)
            {
                if (!strcmp(attr[i], "name"))
                    d->style_set->SetName(attr[i+1]);
            }
        }
        else if (!strcmp(el, "widget"))
        {
            d->style.reset(new Style);
            for (i = 0; attr[i]; i += 2)
            {
                if (!strcmp(attr[i], "type"))
                    d->style->SetType(attr[i+1]);
				if (!strcmp(attr[i], "cursor"))
					d->style->SetCursor(d->factory->Create(attr[i+1], 0, 0, -1, -1));
            }
        }
        else if (!strcmp(el, "back_color"))
        {
            float r, g, b, a;
            for (i = 0; attr[i]; i += 2)
            {
                if (!strcmp(attr[i], "r"))
                    r = (float)atof(attr[i+1]);
                else if (!strcmp(attr[i], "g"))
                    g = (float)atof(attr[i+1]);
                else if (!strcmp(attr[i], "b"))
                    b = (float)atof(attr[i+1]);
                else if (!strcmp(attr[i], "a"))
                    a = (float)atof(attr[i+1]);
            }
            d->style->SetBackColor(Style::BACK_COLOR, r, g, b, a);
        }
        else if (!strcmp(el, "back_color_mouse_over"))
        {
            float r, g, b, a;
            for (i = 0; attr[i]; i += 2)
            {
                if (!strcmp(attr[i], "r"))
                    r = (float)atof(attr[i+1]);
                else if (!strcmp(attr[i], "g"))
                    g = (float)atof(attr[i+1]);
                else if (!strcmp(attr[i], "b"))
                    b = (float)atof(attr[i+1]);
                else if (!strcmp(attr[i], "a"))
                    a = (float)atof(attr[i+1]);
            }
            d->style->SetBackColor(Style::BACK_COLOR_MOUSE_OVER, r, g, b, a);
        }
        else if (!strcmp(el, "back_color_mouse_pressed"))
        {
            float r, g, b, a;
            for (i = 0; attr[i]; i += 2)
            {
                if (!strcmp(attr[i], "r"))
                    r = (float)atof(attr[i+1]);
                else if (!strcmp(attr[i], "g"))
                    g = (float)atof(attr[i+1]);
                else if (!strcmp(attr[i], "b"))
                    b = (float)atof(attr[i+1]);
                else if (!strcmp(attr[i], "a"))
                    a = (float)atof(attr[i+1]);
            }
            d->style->SetBackColor(Style::BACK_COLOR_MOUSE_PRESSED, r, g, b, a);
        }
        else if (!strcmp(el, "back_color_focused"))
        {
            float r, g, b, a;
            for (i = 0; attr[i]; i += 2)
            {
                if (!strcmp(attr[i], "r"))
                    r = (float)atof(attr[i+1]);
                else if (!strcmp(attr[i], "g"))
                    g = (float)atof(attr[i+1]);
                else if (!strcmp(attr[i], "b"))
                    b = (float)atof(attr[i+1]);
                else if (!strcmp(attr[i], "a"))
                    a = (float)atof(attr[i+1]);
            }
            d->style->SetBackColor(Style::BACK_COLOR_FOCUSED, r, g, b, a);
        }
        else if (!strcmp(el, "use_texture"))
        {
            for (i = 0; attr[i]; i += 2)
            {
                if (!strcmp(attr[i], "value"))
                    d->style->EnableTextures(atoi(attr[i+1]) != 0);
            }
        }
        else if (!strcmp(el, "back_texture"))
        {
            std::string filename;
            float x, y, width, height;
            for (i = 0; attr[i]; i += 2)
            {
                if (!strcmp(attr[i], "file"))
                    filename = attr[i+1];
                else if (!strcmp(attr[i], "x"))
                    x = (float)atof(attr[i+1]);
                else if (!strcmp(attr[i], "y"))
                    y = (float)atof(attr[i+1]);
                else if (!strcmp(attr[i], "width"))
                    width = (float)atof(attr[i+1]);
                else if (!strcmp(attr[i], "height"))
                    height = (float)atof(attr[i+1]);
            }
            d->style->SetBackTexture(Style::BACK_COLOR, d->factory->Create(filename, x, y, width, height));
        }
        else if (!strcmp(el, "back_texture_mouse_over"))
        {
            std::string filename;
            float x, y, width, height;
            for (i = 0; attr[i]; i += 2)
            {
                if (!strcmp(attr[i], "file"))
                    filename = attr[i+1];
                else if (!strcmp(attr[i], "x"))
                    x = (float)atof(attr[i+1]);
                else if (!strcmp(attr[i], "y"))
                    y = (float)atof(attr[i+1]);
                else if (!strcmp(attr[i], "width"))
                    width = (float)atof(attr[i+1]);
                else if (!strcmp(attr[i], "height"))
                    height = (float)atof(attr[i+1]);
            }
            d->style->SetBackTexture(Style::BACK_COLOR_MOUSE_OVER, d->factory->Create(filename, x, y, width, height));
        }
        else if (!strcmp(el, "back_texture_mouse_pressed"))
        {
            std::string filename;
            float x, y, width, height;
            for (i = 0; attr[i]; i += 2)
            {
                if (!strcmp(attr[i], "file"))
                    filename = attr[i+1];
                else if (!strcmp(attr[i], "x"))
                    x = (float)atof(attr[i+1]);
                else if (!strcmp(attr[i], "y"))
                    y = (float)atof(attr[i+1]);
                else if (!strcmp(attr[i], "width"))
                    width = (float)atof(attr[i+1]);
                else if (!strcmp(attr[i], "height"))
                    height = (float)atof(attr[i+1]);
            }
            d->style->SetBackTexture(Style::BACK_COLOR_MOUSE_PRESSED, d->factory->Create(filename, x, y, width, height));
        }
        else if (!strcmp(el, "back_texture_focused"))
        {
            std::string filename;
            float x, y, width, height;
            for (i = 0; attr[i]; i += 2)
            {
                if (!strcmp(attr[i], "file"))
                    filename = attr[i+1];
                else if (!strcmp(attr[i], "x"))
                    x = (float)atof(attr[i+1]);
                else if (!strcmp(attr[i], "y"))
                    y = (float)atof(attr[i+1]);
                else if (!strcmp(attr[i], "width"))
                    width = (float)atof(attr[i+1]);
                else if (!strcmp(attr[i], "height"))
                    height = (float)atof(attr[i+1]);
            }
            d->style->SetBackTexture(Style::BACK_COLOR_FOCUSED, d->factory->Create(filename, x, y, width, height));
        }
    }

    void end(void *data, const char *el)
    {
        Buffer* d = (Buffer*)data;

        if (!strcmp(el, "style"))
        {
        }
        else if (!strcmp(el, "widget"))
        {
            d->style_set->SetStyle(d->style->GetType(), d->style);
        }
    }

    void text(void *userData, const XML_Char *s, int len)
    {
    }

     boost::shared_ptr<StyleSet> StyleSet::Create(const std::string& filename, boost::shared_ptr<AbstractPictureFactory> factory)
    {
        XML_Parser p = XML_ParserCreate(NULL);
        if (! p)
            throw std::runtime_error("Couldn't allocate memory for parser");

        XML_SetElementHandler(p, start, end);
        XML_SetCharacterDataHandler(p, text);
        Buffer b;
        b.factory = factory;
        XML_SetUserData(p, &b);

#if _MSC_VER >= 1500
		FILE* f;
		fopen_s(&f, filename.c_str(), "rb");
#else
        FILE* f = fopen(filename.c_str(), "rb");
#endif	//	_MSC_VER

        if (f == 0)
        {
            XML_ParserFree(p);
            throw std::runtime_error("Can't open file " + filename);
        }

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
        return b.style_set;
    }
}
