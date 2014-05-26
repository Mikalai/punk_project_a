//#include <string/module.h>
//#include <attributes/animation/action.h>
//#include "io_string.h"
//#include "io_object.h"
//#include "io_action.h"
//
//PUNK_ENGINE_BEGIN
//namespace IoModule {
//    void SaveAction(Core::Buffer *buffer, const Core::IObject *o)
//    {
//        SaveObject(buffer, o);
//        const Attributes::Action* a = Cast<const Attributes::Action*>(o);
//        buffer->WriteSigned32(a->GetStartFrame());
//        buffer->WriteSigned32(a->GetEndFrame());
//        SaveString(buffer, a->GetName());
//    }
//
//    void LoadAction(Core::Buffer *buffer, Core::IObject *o)
//    {
//        LoadObject(buffer, o);
//        Attributes::Action* a = Cast<Attributes::Action*>(o);
//        a->SetStartFrame(buffer->ReadSigned32());
//        a->SetEndFrame(buffer->ReadSigned32());
//        Core::String value;
//        SaveString(buffer, value);
//        a->SetName(value);
//    }
//}
//PUNK_ENGINE_END
//
