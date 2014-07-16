#include <system/module.h>
#include <core/iserializable.h>
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
		//	first try binary
		Core::Guid clsid;
		buffer.ReadPod(clsid);
		try {
			auto serializable = System::CreateInstancePtr<Core::ISerializable>(clsid, Core::IID_ISerializable);
			if (serializable)
				serializable->Deserialize(buffer);
			return serializable;
		}
		catch (System::Error::SystemException& e) {
			System::GetDefaultLogger()->Error("Can't file " + e.Message());
			buffer.SetOffset(0, 0);
		}
		
        return ParseAnything(buffer);
    }
}
PUNK_ENGINE_END
