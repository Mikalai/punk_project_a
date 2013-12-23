#ifndef FONT_ERROR_H
#define FONT_ERROR_H

#include <config.h>
#include <system/errors/module.h>

PUNK_ENGINE_BEGIN
namespace Font {
    namespace Error {

        class PUNK_ENGINE_API FontError : public System::Error::SystemException {
            using System::Error::SystemException::SystemException;
        };

        class PUNK_ENGINE_API CantDestroyFontBuilder : public FontError {
            using FontError::FontError;
        };

        class PUNK_ENGINE_API CantRenderGlyph : public FontError {
            using FontError::FontError;
        };

        class PUNK_ENGINE_API CantSetGlyphSize : public FontError {
            using FontError::FontError;
        };

        class PUNK_ENGINE_API CantLoadGlyph : public FontError {
            using FontError::FontError;
        };

        class PUNK_ENGINE_API CantOpenFontFile : public FontError {
            using FontError::FontError;
        };

        class PUNK_ENGINE_API UnknownFileFormat : public FontError {
            using FontError::FontError;
        };

        class PUNK_ENGINE_API CantInitializeFontEngine : public FontError {
            using FontError::FontError;
        };
    }
}
PUNK_ENGINE_END

#endif // FONT_ERROR_H
