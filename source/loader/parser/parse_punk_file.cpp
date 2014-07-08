#include <system/module.h>
#include "parser.h"
#include "parse_anything.h"

PUNK_ENGINE_BEGIN
namespace IoModule
{
    Core::Pointer<Core::IObject> ParsePunkFile(const Core::String& path)
    {
		System::GetDefaultLogger()->Info(Core::String("ParseKeyword {0}").arg(path));
        Core::Buffer buffer;
        if (!System::BinaryFile::Load(path, buffer))
			return Core::Pointer < Core::IObject > {nullptr, Core::DestroyObject};
        return ParseAnything(buffer);
    }
}
PUNK_ENGINE_END
