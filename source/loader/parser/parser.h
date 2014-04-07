#ifndef _H_PUNK_VIRTUAL_LOADER
#define _H_PUNK_VIRTUAL_LOADER

#include <loader/error/loader_error.h>
#include "keywords.h"
#include "base_parser2.h"

#define CHECK_START(buffer)\
    if (!Loader::CheckIntegrity(buffer))\
{\
    throw Error::LoaderException(L"Integrity check failed");\
    }

#define CHECK_END(buffer)\
    if (Loader::Parse(buffer.ReadWord()) != WORD_CLOSE_BRACKET)\
{\
    throw Error::LoaderException(L"Integrity check failed");\
    }

PUNK_ENGINE_BEGIN
namespace Loader {
    extern bool CheckIntegrity(Core::Buffer& buffer);
}
PUNK_ENGINE_END

#endif
