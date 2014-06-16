#include <system/environment.h>
#include <loader/error/loader_error.h>
#include "path_finder.h"

PUNK_ENGINE_BEGIN
namespace IoModule
{
    const Core::String FindPath(const Core::String &filename)
    {
        if (filename.EndWith(L".static")
                || filename.EndWith(L".skin")
                || filename.EndWith(L".river")
                || filename.EndWith(L".terrain")
                || filename.EndWith(L".material")
                || filename.EndWith(L".sun")
                || filename.EndWith(L".pmd")
                || filename.EndWith(L"armature")
                || filename.EndWith(L".action")
                || filename.EndWith(L".path")
                || filename.EndWith(L".navi_mesh")
                || filename.EndWith(L".dir_light")
                || filename.EndWith(L".point_light")
                || filename.EndWith(L".spot_light"))
            return System::Environment::Instance()->GetModelFolder() + filename;

        if (filename.EndWith(L".jpg")
                || filename.EndWith(L".png")
                || filename.EndWith(L".tif"))
            return System::Environment::Instance()->GetTextureFolder() + filename;
        throw Error::LoaderException(L"Can't locate resource file: " + filename);
    }
}
PUNK_ENGINE_END
