//#include <string/module.h>
//#include <attributes/skinning/armature.h>
//#include <attributes/skinning/bone.h>
//#include "io_bone.h"
//#include "io_object.h"
//#include "io_armature.h"
//
//PUNK_ENGINE_BEGIN
//using namespace Attributes;
//namespace IoModule {
//    void SaveArmature(Core::Buffer *buffer, const Core::IObject* o)
//    {
//        SaveObject(buffer, 0);
//        const Armature* a = Cast<const Armature*>(o);
//        unsigned count = (unsigned)a->GetRootsBonesCount();
//        buffer->WriteUnsigned32(count);
//        for (auto index = 0; index < count; ++index)
//        {
//            const Bone* root = a->GetRootBone(index);
//            SaveBone(buffer, *root);
//        }
//    }
//
//    void LoadArmature(Core::Buffer *buffer, Core::IObject* o)
//    {
//        LoadObject(buffer, o);
//        Armature* a = Cast<Armature*>(o);
//        a->Clear();
//        unsigned count = buffer->ReadUnsigned32();
//        for (unsigned i = 0; i != count; ++i)
//        {
//            std::unique_ptr<Bone> bone(new Bone);
//            LoadBone(buffer, *bone);
//            a->CacheBones(bone.get());
//            a->AddRootBone(bone.release());
//        }
//    }
//}
//PUNK_ENGINE_END
