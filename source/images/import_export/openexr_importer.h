#ifndef OPENEXR_IMPORTER_H
#define OPENEXR_IMPORTER_H

#include "importer.h"

#ifdef USE_OPENEXR
//#include <OpenEXR/Iex.h>
#endif

PUNK_ENGINE_BEGIN
namespace Image
{

    class OpenEXRImporter : public Importer
    {
    public:
        OpenEXRImporter();
    };
}
PUNK_ENGINE_END

#endif // OPENEXR_IMPORTER_H
