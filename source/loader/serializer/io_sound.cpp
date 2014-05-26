#include "io_sound.h"

PUNK_ENGINE_BEGIN
namespace IoModule {

    PUNK_ENGINE_API void SaveSound(Core::Buffer* buffer, const Attributes::Sound* value) {
        buffer->WriteString(value->GetName());
        buffer->WriteString(value->GetFilename());
        buffer->WriteReal32(value->GetVolume());
        buffer->WriteReal32(value->GetPitch());
        buffer->WriteReal32(value->GetMaxDistance());
        buffer->WriteReal32(value->GetReferenceDistance());
        buffer->WriteReal32(value->GetConeAngleInner());
        buffer->WriteReal32(value->GetConeAngleOuter());
        buffer->WriteReal32(value->GetConeVolumeOuter());
        buffer->WriteReal32(value->GetAttenuation());
    }

    PUNK_ENGINE_API void LoadSound(Core::Buffer* buffer, Attributes::Sound* value) {
        value->SetName(buffer->ReadString());
        value->SetFilename(buffer->ReadString());
        value->SetVolume(buffer->ReadReal32());
        value->SetPitch(buffer->ReadReal32());
        value->SetMaxDistance(buffer->ReadReal32());
        value->SetReferenceDistance(buffer->ReadReal32());
        value->SetConeAngleInner(buffer->ReadReal32());
        value->SetConeAngleOuter(buffer->ReadReal32());
        value->SetConeAngleOuter(buffer->ReadReal32());
        value->SetAttenuation(buffer->ReadReal32());
    }
}
PUNK_ENGINE_END
