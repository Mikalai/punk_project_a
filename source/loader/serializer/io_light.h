#ifndef IO_LIGHT_H
#define IO_LIGHT_H

#include "config.h"

PUNK_ENGINE_BEGIN
namespace Attributes {
    class PointLight;
}
namespace Core {
    class String;
    class Object;
}
namespace Loader {
    Attributes::PointLight* CreateFromFile(const Core::String& path);
    Attributes::PointLight* CreateFromStream(std::istream& stream);

    void Save(Core::Buffer* buffer, const Core::Object* value);
    void Load(Core::Buffer* buffer, Core::Object* value);
}
PUNK_ENGINE_END

#endif // IO_LIGHT_H