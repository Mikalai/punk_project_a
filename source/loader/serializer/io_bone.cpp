#include <string/module.h>
#include <attributes/skinning/bone.h>
#include "io_string.h"
#include "io_matrix.h"
#include "io_bone.h"

PUNK_ENGINE_BEGIN
namespace Loader {

    void SaveBone(Core::Buffer* buffer, const Attributes::Bone& b)
    {
        SaveString(buffer, b.GetName());
        SaveString(buffer, b.GetParentName());
        SaveMatrix4f(buffer, b.GetWorldMatrix());
        SaveMatrix4f(buffer, b.GetBoneMatrix());

        unsigned children_count = b.GetChildren().size();
        buffer->WriteUnsigned32(children_count);
        for (auto bone : b.GetChildren())
        {
            SaveBone(buffer, *bone);
        }
    }

    void LoadBone(Core::Buffer* buffer, Attributes::Bone& bone)
    {
        bone.Clear();
        Core::String name;
        LoadString(buffer, name);
        bone.SetName(name);

        Core::String parent_name;
        LoadString(buffer, parent_name);
        bone.SetParentName(parent_name);

        Math::mat4 matrix;
        LoadMatrix4f(buffer, matrix);
        bone.SetWorldMatrix(matrix);

        LoadMatrix4f(buffer, matrix);
        bone.SetBoneMatrix(matrix);

        unsigned children_count = buffer->ReadUnsigned32();
        for (unsigned i = 0; i != children_count; ++i)
        {
            std::unique_ptr<Attributes::Bone> child(new Attributes::Bone);
            LoadBone(buffer, *child);
            bone.AddChild(child.release());
        }
    }
}
PUNK_ENGINE_END
