//#include <fstream>
//#include <memory>
//#include <system/environment.h>
//#include <graphics/module.h>
//#include <attributes/animation/module.h>
//#include <attributes/skinning/module.h>
//#include "skin_geometry.h"
//
//PUNK_ENGINE_BEGIN
//namespace Attributes
//{
//	Core::Rtti SkinGeometryType{ "Attributes.SkinGeometry", typeid(SkinGeometry).hash_code(), { Geometry::Type() } };
//
//	Core::Rtti* SkinGeometry::Type() {
//		return &SkinGeometryType;
//	}
//
//    SkinGeometry::GpuCache::GpuCache(SkinGeometry& value)
//        : m_geom(value)
//        , m_gpu_buffer(nullptr)
//    {
//    }
//
//    SkinGeometry::GpuCache::~GpuCache()
//    {
//        Drop();
//    }
//
//    bool SkinGeometry::GpuCache::IsOnGpu()
//    {
//        return m_gpu_buffer != nullptr;
//    }
//
//    size_t SkinGeometry::GpuCache::GetGpuMemoryUsage() const
//    {
//        return m_gpu_buffer->GetMemoryUsage();
//    }
//
//    void SkinGeometry::GpuCache::Drop()
//    {
//        delete m_gpu_buffer;
//        m_gpu_buffer = nullptr;
//    }
//
//    bool CookOneVertexWithBone(const SkinGeometry* mesh, const Armature* armature, int index, Math::vec4& bone, Math::vec4& weight);
//
//  
//    void SkinGeometry::GpuCache::Update(Armature* armature, Graphics::IVideoDriver* driver)
//    {
//        if (!m_geom.GetCpuCache().IsOnCpu())
//            m_geom.GetCpuCache().Update();
//
//        Drop();
//
//        Graphics::IVertexArray* vb = nullptr;
//        Graphics::IIndexArray* ib = nullptr;
//
//        if (!Cook(&m_geom, armature, vb, ib))
//            return;
//
//        Graphics::ITrianglesPointer mesh = Graphics::CreateTriangles(vb->GetVertexType(), driver);
//        mesh->Cook(vb, ib);
//        m_gpu_buffer = mesh.release();
//    }
//
//    Graphics::IRenderable* SkinGeometry::GpuCache::GetGpuBuffer()
//    {
//        return m_gpu_buffer;
//    }
//
//    SkinGeometry::CpuCache::CpuCache(SkinGeometry &value)
//        : m_geom(value)
//        , m_is_on_cpu(false)
//    {}
//
//
//    void SkinGeometry::CpuCache::SetVertices(const Vertices& value)
//    {
//        m_vertices = value;
//        m_is_on_cpu = true;
//        m_geom.m_bbox.Create(&m_vertices[0], m_vertices.size());
//        m_geom.m_sphere.Create(&m_vertices[0], m_vertices.size());
//    }
//
//    void SkinGeometry::CpuCache::SetNormals(const Normals& value)
//    {
//        m_normals = value;
//    }
//
//    void SkinGeometry::CpuCache::SetFaces(const Faces& value)
//    {
//        m_faces = value;
//    }
//
//    void SkinGeometry::CpuCache::SetTextureMeshes(const TextureMeshes& value)
//    {
//        m_tex_coords = value;
//    }
//
//    void SkinGeometry::CpuCache::SetBoneWeights(const BoneWeights &value)
//    {
//        m_bone_weights = value;
//    }
//
//    const SkinGeometry::Vertices& SkinGeometry::CpuCache::GetVertices() const
//    {
//        return m_vertices;
//    }
//
//    const SkinGeometry::Normals& SkinGeometry::CpuCache::GetNormals() const
//    {
//        return m_normals;
//    }
//
//    const SkinGeometry::Faces& SkinGeometry::CpuCache::GetFaces() const
//    {
//        return m_faces;
//    }
//
//    const SkinGeometry::TextureMeshes& SkinGeometry::CpuCache::GetTextureMeshes() const
//    {
//        return m_tex_coords;
//    }
//
//    const SkinGeometry::BoneWeights& SkinGeometry::CpuCache::GetBoneWeights() const
//    {
//        return m_bone_weights;
//    }
//
//    SkinGeometry::Vertices& SkinGeometry::CpuCache::GetVertices()
//    {
//        return m_vertices;
//    }
//
//    SkinGeometry::Normals& SkinGeometry::CpuCache::GetNormals()
//    {
//        return m_normals;
//    }
//
//    SkinGeometry::Faces& SkinGeometry::CpuCache::GetFaces()
//    {
//        return m_faces;
//    }
//
//    SkinGeometry::TextureMeshes& SkinGeometry::CpuCache::GetTextureMeshes()
//    {
//        return m_tex_coords;
//    }
//
//    SkinGeometry::BoneWeights& SkinGeometry::CpuCache::GetBoneWeights()
//    {
//        return m_bone_weights;
//    }
//
//    bool SkinGeometry::CpuCache::IsOnCpu()
//    {
//        return m_is_on_cpu;
//    }
//
//    void SkinGeometry::CpuCache::Drop()
//    {
//        m_is_on_cpu = false;
//        Vertices v;
//        m_vertices.swap(v);
//        Normals n;
//        m_normals.swap(n);
//        Faces f;
//        m_faces.swap(f);
//        TextureMeshes t;
//        m_tex_coords.swap(t);
//        BoneWeights w;
//        m_bone_weights.swap(w);
//    }
//
//    void SkinGeometry::CpuCache::Update(const Core::String &path)
//    {
////        Drop();
////        SkinGeometry* geom = dynamic_cast<SkinGeometry*>(Utility::ParsePunkFile(path));
////        if (!geom)
////            return;
////        m_geom.SetVertices(geom->GetVertices());
////        m_geom.SetNormals(geom->GetNormals());
////        m_geom.SetFaces(geom->GetFaces());
////        m_geom.SetTextureMeshes(geom->GetTextureMeshes());
////        m_geom.SetWorldOffset(geom->GetWorldOffset());
////        m_geom.SetBoneWeights(geom->GetBoneWeights());
////        m_is_on_cpu = true;
////        delete geom;
//    }
//
//    void SkinGeometry::CpuCache::Update()
//    {
////        Drop();
////        SkinGeometry* geom = dynamic_cast<SkinGeometry*>(Utility::ParsePunkFile(System::Environment::Instance()->GetModelFolder() + m_geom.GetFilename()));
////        if (!geom)
////            return;
////        m_geom.SetVertices(geom->GetVertices());
////        m_geom.SetNormals(geom->GetNormals());
////        m_geom.SetFaces(geom->GetFaces());
////        m_geom.SetTextureMeshes(geom->GetTextureMeshes());
////        m_geom.SetWorldOffset(geom->GetWorldOffset());
////        m_geom.SetBoneWeights(geom->GetBoneWeights());
////        m_is_on_cpu = true;
////        delete geom;
//    }
//
//    size_t SkinGeometry::CpuCache::GetCpuMemoryUsage() const
//    {
//        size_t res = 0;
//        res += m_vertices.size() * sizeof(m_vertices[0]);
//        res += m_normals.size() * sizeof(m_normals[0]);
//        res += m_faces.size() * sizeof(m_faces[0]);
//        for (auto i : m_tex_coords)
//        {
//            res += i.second.size() * sizeof(i.second[0]);
//        }
//
//        return res;
//    }
//
//    void SkinGeometry::CpuCache::Save(Core::Buffer *buffer) const
//    {
////        if (m_vertices.empty() || m_normals.empty() || m_faces.empty() || m_tex_coords.empty())
////            throw System::Error::SystemException(L"Can't save static geometry");
//
////        buffer->WriteSigned32((int)m_vertices.size());
////        for (auto& v : m_vertices)
////            Math::SaveVector3f(buffer, v);
//
////        buffer->WriteSigned32((int)m_faces.size());
////        for (auto& v : m_faces)
////            Math::SaveVector3i(buffer, v);
//
////        buffer->WriteSigned32((int)m_normals.size());
////        for (auto& v : m_normals)
////            Math::SaveVector3f(buffer, v);
//
////        int count = (int)m_tex_coords.size();
////        buffer->WriteSigned32(count);
////        for (auto it = m_tex_coords.begin(); it != m_tex_coords.end(); ++it)
////        {
////            buffer->WriteString(it->first);
////            int size = (int)it->second.size();
////            buffer->WriteSigned32(size);
////            for (auto& v : it->second)
////                for (int i = 0; i != 4; ++i)
////                    v[i].Save(buffer);
////        }
//
////        count = m_bone_weights.size();
////        buffer->WriteSigned32(count);
////        for (auto it : m_bone_weights)
////        {
////            int index = it.first;
////            buffer->WriteSigned32(index);
////            int count = it.second.size();
////            buffer->WriteSigned32(count);
////            for (auto it2 : it.second)
////            {
////                buffer->WriteString(it2.first);
////                float weight = it2.second;
////                buffer->WriteReal32(weight);
////            }
////        }
//    }
//
//    void SkinGeometry::CpuCache::Load(Core::Buffer *buffer)
//    {
////        int size = buffer->ReadSigned32();
////        m_vertices.resize(size);
////        for (int i = 0; i != size; ++i)
////            Math::LoadVector3f(buffer, m_vertices[i]);
//
////        size = buffer->ReadSigned32();
////        m_faces.resize(size);
////        for (int i = 0; i != size; ++i)
////            Math::LoadVector3i(buffer, m_faces[i]);
//
////        size = buffer->ReadSigned32();
////        for (int i = 0; i != size; ++i)
////            Math::LoadVector3f(buffer, m_normals[i]);
//
////        int count = buffer->ReadSigned32();
////        for (int i = 0; i < count; ++i)
////        {
////            Core::String name = buffer->ReadString();
////            size = buffer->ReadSigned32();
////            std::vector<std::array<Math::vec2, 4>> v;
////            v.resize(size);
////            for (auto& p : v)
////                for (int j = 0; j != 4; ++j)
////                    p[j].Load(buffer);
////            m_tex_coords[name] = v;
////        }
//
////        count = buffer->ReadSigned32();
////        for (int i = 0; i != count; ++i)
////        {
////            int index = buffer->ReadSigned32();
////            int num_bones = buffer->ReadSigned32();
////            for (int j = 0; j != num_bones; ++j)
////            {
////                Core::String name = buffer->ReadString();
////                float weight = buffer->ReadReal32();
////                m_bone_weights[index][name] = weight;
////            }
////        }
////        m_is_on_cpu = true;
//    }
//
//    SkinGeometry::SkinGeometry()
//        : m_cpu_cache(*this)
//        , m_gpu_cache(*this)
//    {
//    }
//
//    SkinGeometry::~SkinGeometry()
//    {
//    }
//
//    SkinGeometry::Vertices& SkinGeometry::GetVertexArray()
//    {
//        return m_cpu_cache.GetVertices();
//    }
//
//    SkinGeometry::Normals& SkinGeometry::GetNormalArray()
//    {
//        return m_cpu_cache.GetNormals();
//    }
//
//    SkinGeometry::Faces& SkinGeometry::GetFaceArray()
//    {
//        return m_cpu_cache.GetFaces();
//    }
//
//    const SkinGeometry::Vertices& SkinGeometry::GetVertexArray() const
//    {
//        return m_cpu_cache.GetVertices();
//    }
//
//    const SkinGeometry::Normals& SkinGeometry::GetNormalArray() const
//    {
//        return m_cpu_cache.GetNormals();
//    }
//
//    const SkinGeometry::Faces& SkinGeometry::GetFaceArray() const
//    {
//        return m_cpu_cache.GetFaces();
//    }
//
//    void SkinGeometry::SetVertices(const SkinGeometry::Vertices& value)
//    {
//        m_cpu_cache.SetVertices(value);
//    }
//
//    void SkinGeometry::SetNormals(const Normals& value)
//    {
//        m_cpu_cache.SetNormals(value);
//    }
//
//    void SkinGeometry::SetFaces(const SkinGeometry::Faces& value)
//    {
//        m_cpu_cache.SetFaces(value);
//    }
//
//    void SkinGeometry::SetTextureMeshes(const SkinGeometry::TextureMeshes& value)
//    {
//        m_cpu_cache.SetTextureMeshes(value);
//    }
//
//    void SkinGeometry::SetBoneWeights(const BoneWeights &value)
//    {
//        m_cpu_cache.SetBoneWeights(value);
//    }
//
//    const SkinGeometry::Vertices& SkinGeometry::GetVertices() const
//    {
//        return m_cpu_cache.GetVertices();
//    }
//
//    const SkinGeometry::Normals& SkinGeometry::GetNormals() const
//    {
//        return m_cpu_cache.GetNormals();
//    }
//
//    const SkinGeometry::Faces& SkinGeometry::GetFaces() const
//    {
//        return m_cpu_cache.GetFaces();
//    }
//
//    const SkinGeometry::TextureMeshes& SkinGeometry::GetTextureMeshes() const
//    {
//        return m_cpu_cache.GetTextureMeshes();
//    }
//
//    const SkinGeometry::BoneWeights& SkinGeometry::GetBoneWeights() const
//    {
//        return m_cpu_cache.GetBoneWeights();
//    }
//
//    void SkinGeometry::SetWorldOffset(const Math::mat4& value)
//    {
//        m_world_offset = value;
//    }
//
//    const Math::mat4& SkinGeometry::GetWorldOffset() const
//    {
//        return m_world_offset;
//    }
//
//    void SkinGeometry::SetFilename(const Core::String& filename)
//    {
//        m_filename = filename;
//    }
//
//    const Core::String& SkinGeometry::GetFilename() const
//    {
//        return m_filename;
//    }
//
//    SkinGeometry::GpuCache& SkinGeometry::GetGpuCache()
//    {
//        return m_gpu_cache;
//    }
//
//    SkinGeometry::CpuCache& SkinGeometry::GetCpuCache()
//    {
//        return m_cpu_cache;
//    }
//
//    void SkinGeometry::SetArmatureName(const Core::String& name)
//    {
//        m_armature_name = name;
//    }
//
//    const Core::String& SkinGeometry::GetArmatureName() const
//    {
//        return m_armature_name;
//    }
//
//    void SkinGeometry::SetName(const Core::String& value)
//    {
//        m_name = value;
//    }
//
//    const Core::String& SkinGeometry::GetName() const
//    {
//        return m_name;
//    }
//}
//PUNK_ENGINE_END
