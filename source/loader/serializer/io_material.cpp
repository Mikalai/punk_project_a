//#include <attributes/data/material.h>
//#include "io_object.h"
//#include "io_string.h"
//#include "io_vector.h"
//#include "io_material.h"
//
//PUNK_ENGINE_BEGIN
//namespace IoModule {
//    PUNK_ENGINE_API void SaveMaterial(Core::Buffer* buffer, const Core::IObject* o)
//    {
//        SaveObject(buffer, o);
//        const Attributes::Material* m = Cast<const Attributes::Material*>(o);
//        SaveString(buffer, m->GetDiffuseMap());
//        SaveString(buffer, m->GetNormalMap());
//        SaveString(buffer, m->GetName());
//        SaveVector4f(buffer, m->GetDiffuseColor());
//        SaveVector4f(buffer, m->GetSpecularColor());
//        SaveVector4f(buffer, m->GetMirrorColor());
//        buffer->WriteReal32(m->GetSpecularFactor());
//        buffer->WriteReal32(m->GetAmbient());
//        buffer->WriteReal32(m->GetDiffuseIntensity());
//        buffer->WriteReal32(m->GetDarkness());
//        buffer->WriteReal32(m->GetDiffuseFresnel());
//        buffer->WriteReal32(m->GetDiffuseFresnelFactor());
//        buffer->WriteReal32(m->GetEmit());
//        buffer->WriteReal32(m->GetRoughness());
//        buffer->WriteReal32(m->GetSpecularIntensity());
//        buffer->WriteReal32(m->GetSpecularIndexOfRefraction());
//        buffer->WriteReal32(m->GetSpecularSlope());
//        buffer->WriteReal32(m->GetTranslucency());
//    }
//
//    void LoadMaterial(Core::Buffer* buffer, Core::IObject* o)
//    {
//        LoadObject(buffer, o);
//        Attributes::Material* m = Cast<Attributes::Material*>(o);
//        {
//            Core::String value;
//            LoadString(buffer, value);
//            m->SetDiffuseMap(value);
//            LoadString(buffer, value);
//            m->SetNormalMap(value);
//            LoadString(buffer, value);
//            m->SetName(value);
//        }
//        {
//            Math::vec4 value;
//            LoadVector4f(buffer, value);
//            m->SetDiffuseColor(value);
//            LoadVector4f(buffer, value);
//            m->SetSpecularColor(value);
//            LoadVector4f(buffer, value);
//            m->SetMirrorColor(value);
//        }
//        m->SetSpecularFactor(buffer->ReadReal32());
//        m->SetAmbient(buffer->ReadReal32());
//        m->SetDiffuseIntensity(buffer->ReadReal32());
//        m->SetDarkness(buffer->ReadReal32());
//        m->SetDiffuseFresnel(buffer->ReadReal32());
//        m->SetDiffuseFresnelFactor(buffer->ReadReal32());
//        m->SetEmit(buffer->ReadReal32());
//        m->SetRoughness(buffer->ReadReal32());
//        m->SetSpecularIntensity(buffer->ReadReal32());
//        m->SetSpecularIndexOfRefraction(buffer->ReadReal32());
//        m->SetSpecularSlope(buffer->ReadReal32());
//        m->SetTranslucency(buffer->ReadReal32());
//    }
//}
//PUNK_ENGINE_END
