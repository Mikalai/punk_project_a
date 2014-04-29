#include <system/module.h>
#include "parser.h"
#include "parse_anything.h"

PUNK_ENGINE_BEGIN
namespace Loader
{
    Core::Object* ParsePunkFile(const Core::String& path)
    {
		System::GetDefaultLogger()->Info(Core::String("Parse {0}").arg(path));
        Core::Buffer buffer;
        if (!System::BinaryFile::Load(path, buffer))
            return nullptr;
        return ParseAnything(buffer);
    }
}
PUNK_ENGINE_END
