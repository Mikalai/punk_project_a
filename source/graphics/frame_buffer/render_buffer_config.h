#ifndef RENDERBUFFERCONFIG_H
#define RENDERBUFFERCONFIG_H

#include <string/module.h>
#include <images/formats.h>

PUNK_ENGINE_BEGIN
namespace Graphics {

    class PUNK_ENGINE_API RenderBufferConfig {
    public:
        RenderBufferConfig();

        void Name(const Core::String& value);
        const Core::String& Name() const;

        void Format(ImageModule::ImageFormat value);
        ImageModule::ImageFormat Format() const;

        void Bits(int value);
        int Bits() const;

    private:
        Core::String m_name;
        ImageModule::ImageFormat m_format;
        int m_bits;
    };
}
PUNK_ENGINE_END

#endif // RENDERBUFFERCONFIG_H
