void SaveNaviMesh(Core::Buffer *buffer, const Core::Object *o)
{
    System::SaveObject(buffer, o);
    const NaviMesh* m = Cast<const NaviMesh*>(o);
    System::SaveString(buffer, m->m_name);
    Math::SaveMatrix4f(buffer, m->m_transfrom);
    unsigned size = m->m_points.size();
    buffer->WriteUnsigned32(size);
    for (auto& p : m->m_points)
    {
        Math::SaveVector3f(buffer, p);
    }

    size = m->m_normals.size();
    buffer->WriteUnsigned32(size);
    for (auto& p : m->m_normals)
    {
        Math::SaveVector3f(buffer, p);
    }

    size = m->m_points.size();
    buffer->WriteUnsigned32(size);
    for (auto& p : m->m_faces)
    {
        Math::SaveVector3i(buffer, p);
    }
}

void LoadNaviMesh(Core::Buffer *buffer, Core::Object *o)
{
    System::LoadObject(buffer, o);
    NaviMesh* m = Cast<NaviMesh*>(o);
    System::LoadString(buffer, m->m_name);
    Math::LoadMatrix4f(buffer, m->m_transfrom);
    unsigned size = buffer->ReadUnsigned32();
    m->m_points.resize(size);
    for (auto& p : m->m_points)
    {
        Math::LoadVector3f(buffer, p);
    }

    size = buffer->ReadUnsigned32();
    m->m_normals.resize(size);
    for (auto& p : m->m_normals)
    {
        Math::LoadVector3f(buffer, p);
    }

    size = buffer->ReadUnsigned32();
    m->m_points.resize(size);
    for (auto& p : m->m_faces)
    {
        Math::LoadVector3i(buffer, p);
    }
}
