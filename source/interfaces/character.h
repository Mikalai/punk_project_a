#ifndef CHARACTER_H
#define CHARACTER_H

#include <config.h>
#include <core/iobject.h>

PUNK_ENGINE_BEGIN

DECLARE_PUNK_GUID(CLSID_Character, "E6768CF9-DF23-48B5-88A6-003D35D10182");

class CharacterFactory {
public:
    void CreateInstance(const Core::Guid& clsid, const Core::Guid& iid, void** instance);
};

PUNK_ENGINE_END


#endif // CHARACTER_H
