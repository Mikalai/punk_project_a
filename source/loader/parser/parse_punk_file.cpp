#include <system/module.h>
#include "parser.h"
#include "parse_anything.h"

PUNK_ENGINE_BEGIN
namespace IoModule
{
    Core::IObject* ParsePunkFile(const Core::String& path)
    {
		System::GetDefaultLogger()->Info(Core::String("ParseKeyword {0}").arg(path));
        Core::Buffer buffer;
        if (!System::BinaryFile::Load(path, buffer))
            return nullptr;
        return ParseAnything(buffer);
    }
}
PUNK_ENGINE_END
