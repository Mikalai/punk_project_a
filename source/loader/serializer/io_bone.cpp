#include "io_bone.h"

void SaveBone(Core::Buffer* buffer, const Bone& b)
{
    System::SaveString(buffer, b.m_name);
    System::SaveString(buffer, b.m_parent_name);
    Math::SaveMatrix4f(buffer, b.m_global_matrix);
    Math::SaveMatrix4f(buffer, b.m_bone_matrix);

    unsigned children_count = b.m_children.size();
    buffer->WriteUnsigned32(children_count);
    for (auto bone : b.m_children)
    {
        SaveBone(buffer, *bone);
    }
}

void LoadBone(Core::Buffer* buffer, Bone& bone)
{
    bone.Clear();
    System::LoadString(buffer, bone.m_name);
    System::LoadString(buffer, bone.m_parent_name);
    Math::LoadMatrix4f(buffer, bone.m_global_matrix);
    Math::LoadMatrix4f(buffer, bone.m_bone_matrix);

    unsigned children_count = buffer->ReadUnsigned32();
    for (unsigned i = 0; i != children_count; ++i)
    {
        std::unique_ptr<Bone> child(new Bone);
        LoadBone(buffer, *child);
        bone.AddChild(child.release());
    }
}
