#ifndef CACHE_DATA_H
#define CACHE_DATA_H

#include <config.h>

PUNK_ENGINE_BEGIN
namespace Font {

    struct CacheData {
        unsigned char* buffer;
        int width;
        int height;
        int x_offset;
        int y_offset;
        int x_advance;
        int y_advance;
    };
}
PUNK_ENGINE_END

#endif // CACHE_DATA_H
