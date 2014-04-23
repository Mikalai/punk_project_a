#include <fstream>
#include <memory>
#include <system/environment.h>
#include <graphics/module.h>
#include "static_geometry.h"

PUNK_ENGINE_BEGIN
namespace Attributes
{
    Core::Rtti StaticGeometryType{"Attributes.StaticGeometry", typeid(StaticGeometry).hash_code(), {Geometry::Type()}};

	Core::Rtti* StaticGeometry::Type() {
		return &StaticGeometryType;
	}

    StaticGeometry::GpuCache::GpuCache(StaticGeometry& value)
        : m_geom(value)
        , m_gpu_buffer(nullptr)
    {}

    StaticGeometry::GpuCache::~GpuCache()
    {
        Drop();
    }

    bool StaticGeometry::GpuCache::IsOnGpu()
    {
        return m_gpu_buffer != nullptr;
    }

    size_t StaticGeometry::GpuCache::GetGpuMemoryUsage() const
    {
        return m_gpu_buffer->GetMemoryUsage();
    }

    void StaticGeometry::GpuCache::Drop()
    {
        delete m_gpu_buffer;
        m_gpu_buffer = nullptr;
    }

    bool CookPositionNormalTangentBitangentTexture0(StaticGeometry* mesh,
                                                    Graphics::IVertexArray*& _vb,
                                                    Graphics::IIndexArray*& _ib)
    {
        using namespace Graphics;

        using CurrentVertex = Vertex<VertexComponent::Position,
        VertexComponent::Normal,
        VertexComponent::Tangent,
        VertexComponent::Bitangent,
        VertexComponent::Texture0>;

        if (mesh->GetVertices().empty())
            throw System::Error::SystemException(L"Can't create static mesh from empty vertex list in mesh descriptor");
        if (mesh->GetTextureMeshes().empty())
            throw System::Error::SystemException(L"Can't create static mesh from mesh descriptor with empty texture coordinates list");
        if (mesh->GetNormals().empty())
            throw System::Error::SystemException(L"Can't create static mesh from mesh descriptor with empty normals list");

        std::vector<unsigned> ib(mesh->GetFaces().size()*3);

        for (unsigned i = 0; i < ib.size(); i++)
            ib[i] = i;

        std::vector<CurrentVertex> vb(mesh->GetFaces().size()*3);

        std::vector<int> base_index;		/// contains vertex index in the source array
        int index = 0;
        for (unsigned i = 0, max_i = mesh->GetTextureMeshes().begin()->second.size(); i < max_i; i++)
        {
            const Math::ivec3& f = mesh->GetFaces()[i];
            const Math::vec3 position[3] = { mesh->GetVertices()[f[0]], mesh->GetVertices()[f[1]], mesh->GetVertices()[f[2]] };
            const Math::vec2 texture[3] = { mesh->GetTextureMeshes().begin()->second[i][0], mesh->GetTextureMeshes().begin()->second[i][1], mesh->GetTextureMeshes().begin()->second[i][2] };
            const Math::vec3 normal[3] = { mesh->GetNormals()[f[0]], mesh->GetNormals()[f[1]], mesh->GetNormals()[f[2]] };

            Math::vec3 tgn;
            Math::vec3 nrm;
            Math::vec3 btn;
            float det;

            for (int j = 0; j < 3; ++j)
            {
                int index_0 = j;
                int index_1 = (j+1)%3;
                int index_2 = (j+2)%3;

                Math::CalculateTBN(position[index_0], position[index_1], position[index_2], texture[index_0], texture[index_1], texture[index_2], tgn, btn, nrm, det);

                det = (det < 0) ? -1.0f : 1.0f;

                vb[index].m_position = position[index_0];
                vb[index].m_normal = normal[index_0];
                vb[index].m_texture0.Set(texture[index_0][0], texture[index_0][1], 0, 0);
                vb[index].m_tangent.Set(tgn[0], tgn[1], tgn[2], det);
                vb[index].m_bitangent.Set(btn[0], btn[1], btn[2], 0);
                base_index.push_back(f[j]);
                index++;
            }
        }

        /// Smooth TBN
        std::vector<int> mask(vb.size());
        for (int i = 0; i < (int)vb.size(); i++)
        {
            Math::vec3 norm;
            Math::vec3 tang;
            Math::vec3 btan;
            for (int j = 0; j < (int)vb.size(); j++)
            {
                CurrentVertex* v = &vb[j];
                if (base_index[j] == i)
                {
                    norm += v->m_normal.XYZ();
                    tang += v->m_tangent.XYZ();
                    btan += v->m_bitangent.XYZ();
                }
            }

            norm.Normalize();
            tang.Normalize();
            btan.Normalize();
            tang = (tang - norm.Dot(tang)*norm).Normalized();
            btan = (btan - norm.Dot(btan)*norm - tang.Dot(btan)*tang).Normalized();

            Math::Matrix<float> m(3,3);
            m.At(0,0) = tang[0]; m.At(0,1) = tang[1]; m.At(0,2) = tang[2];
            m.At(1,0) = btan[0]; m.At(1,1) = btan[1]; m.At(1,2) = btan[2];
            m.At(2,0) = norm[0]; m.At(2,1) = norm[1]; m.At(2,2) = norm[2];
            float w = m.Determinant();

            for (int j = 0; j < (int)vb.size(); j++)
            {
                CurrentVertex* v = &vb[j];
                if (base_index[j] == i)
                {
                    v->m_normal = norm;
                    v->m_tangent.Set(tang[0], tang[1], tang[2], w);
                    v->m_bitangent = btan;
                }
            }
        }

        _vb = new VertexArray<CurrentVertex>(vb);
        _ib = new IndexArray<unsigned>(ib);
        return true;
    }

    bool CookPositionNormal(StaticGeometry* mesh,
                            Graphics::IVertexArray*& _vb,
                            Graphics::IIndexArray*& _ib)
    {
        using namespace Graphics;
        using CurrentVertex = Vertex<VertexComponent::Position, VertexComponent::Normal>;

        if (mesh->GetVertices().empty())
            throw System::Error::SystemException(L"Can't create static mesh from empty vertex list in mesh descriptor");
        if (mesh->GetNormals().empty())
            throw System::Error::SystemException(L"Can't create static mesh from mesh descriptor with empty normals list");

        std::vector<unsigned> ib(mesh->GetFaces().size()*3);

        for (unsigned i = 0; i < ib.size(); i++)
            ib[i] = i;

        std::vector<CurrentVertex> vb(mesh->GetFaces().size()*3);

        std::vector<int> base_index;		/// contains vertex index in the source array
        int index = 0;
        for (unsigned i = 0, max_i = mesh->GetFaces().size(); i < max_i; i++)
        {
            const Math::ivec3& f = mesh->GetFaces()[i];
            const Math::vec3 position[3] = { mesh->GetVertices()[f[0]], mesh->GetVertices()[f[1]], mesh->GetVertices()[f[2]] };
            const Math::vec3 normal[3] = { mesh->GetNormals()[f[0]], mesh->GetNormals()[f[1]], mesh->GetNormals()[f[2]] };

            for (int j = 0; j < 3; ++j)
            {
                vb[index].m_position = position[j];
                vb[index].m_normal = normal[j];
                base_index.push_back(f[j]);
                index++;
            }
        }

        /// Smooth TBN
        std::vector<int> mask(vb.size());
        for (int i = 0; i < (int)vb.size(); i++)
        {
            Math::vec3 norm;
            for (int j = 0; j < (int)vb.size(); j++)
            {
                CurrentVertex* v = &vb[j];
                if (base_index[j] == i)
                {
                    norm += v->m_normal.XYZ();
                }
            }

            norm.Normalize();

            for (int j = 0; j < (int)vb.size(); j++)
            {
                CurrentVertex* v = &vb[j];
                if (base_index[j] == i)
                {
                    v->m_normal = norm;
                }
            }
        }

        _vb = new VertexArray<CurrentVertex>(vb);
        _ib = new IndexArray<unsigned>(ib);

        return true;
    }

    bool CookPosition(StaticGeometry* mesh,
                      Graphics::IVertexArray*& _vb,
                      Graphics::IIndexArray*& _ib)
    {
        using namespace Graphics;
        using CurrentVertex = Vertex<VertexComponent::Position>;

        if (mesh->GetVertices().empty())
            throw System::Error::SystemException(L"Can't create static mesh from empty vertex list in mesh descriptor");

        std::vector<unsigned> ib(mesh->GetFaces().size()*3);

        for (unsigned i = 0; i < ib.size(); i++)
            ib[i] = i;

        std::vector<CurrentVertex> vb(mesh->GetFaces().size()*3);

        std::vector<int> base_index;		/// contains vertex index in the source array
        int index = 0;
        for (unsigned i = 0, max_i = mesh->GetFaces().size(); i < max_i; i++)
        {
            const Math::ivec3& f = mesh->GetFaces()[i];
            const Math::vec3 position[3] = { mesh->GetVertices()[f[0]], mesh->GetVertices()[f[1]], mesh->GetVertices()[f[2]] };

            for (int j = 0; j < 3; ++j)
            {
                vb[index].m_position = position[j];
                base_index.push_back(f[j]);
                index++;
            }
        }

        _vb = new VertexArray<CurrentVertex>(vb);
        _ib = new IndexArray<unsigned>(ib);

        return true;
    }

    bool CookPositionTexture0(StaticGeometry* mesh,
                              Graphics::IVertexArray*& _vb,
                              Graphics::IIndexArray*& _ib)
    {
        using namespace Graphics;
        using CurrentVertex = Vertex<VertexComponent::Position, VertexComponent::Texture0>;

        if (mesh->GetVertices().empty())
            throw System::Error::SystemException(L"Can't create static mesh from empty vertex list in mesh descriptor");
        if (mesh->GetTextureMeshes().empty())
            throw System::Error::SystemException(L"Can't create static mesh from mesh descriptor with empty texture coordinates list");

        std::vector<unsigned> ib(mesh->GetFaces().size()*3);

        for (unsigned i = 0; i < ib.size(); i++)
            ib[i] = i;

        std::vector<CurrentVertex> vb(mesh->GetFaces().size()*3);

        std::vector<int> base_index;		/// contains vertex index in the source array
        int index = 0;
        for (unsigned i = 0, max_i = mesh->GetTextureMeshes().begin()->second.size(); i < max_i; i++)
        {
            const Math::ivec3& f = mesh->GetFaces()[i];
            const Math::vec3 position[3] = { mesh->GetVertices()[f[0]], mesh->GetVertices()[f[1]], mesh->GetVertices()[f[2]] };
            const Math::vec2 texture[3] = { mesh->GetTextureMeshes().begin()->second[i][0], mesh->GetTextureMeshes().begin()->second[i][1], mesh->GetTextureMeshes().begin()->second[i][2] };

            for (int j = 0; j < 3; ++j)
            {
                vb[index].m_position = position[j];
                vb[index].m_texture0.Set(texture[j][0], texture[j][1], 0, 0);
                base_index.push_back(f[j]);
                index++;
            }
        }

        _vb = new VertexArray<CurrentVertex>(vb);
        _ib = new IndexArray<unsigned>(ib);

        return true;
    }

    bool CookPositionNormalTexture0(StaticGeometry* mesh,
                                    Graphics::IVertexArray*& _vb,
                                    Graphics::IIndexArray*& _ib)
    {
        using namespace Graphics;
        using CurrentVertex = Vertex<VertexComponent::Position, VertexComponent::Normal, VertexComponent::Texture0>;

        if (mesh->GetVertices().empty())
            throw System::Error::SystemException(L"Can't create static mesh from empty vertex list in mesh descriptor");
        if (mesh->GetTextureMeshes().empty())
            throw System::Error::SystemException(L"Can't create static mesh from mesh descriptor with empty texture coordinates list");
        if (mesh->GetNormals().empty())
            throw System::Error::SystemException(L"Can't create static mesh from mesh descriptor with empty normals list");

        std::vector<unsigned> ib(mesh->GetFaces().size()*3);

        for (unsigned i = 0; i < ib.size(); i++)
            ib[i] = i;

        std::vector<CurrentVertex> vb(mesh->GetFaces().size()*3);

        std::vector<int> base_index;		/// contains vertex index in the source array
        int index = 0;
        for (unsigned i = 0, max_i = mesh->GetTextureMeshes().begin()->second.size(); i < max_i; i++)
        {
            const Math::ivec3& f = mesh->GetFaces()[i];
            const Math::vec3 position[3] = { mesh->GetVertices()[f[0]], mesh->GetVertices()[f[1]], mesh->GetVertices()[f[2]] };
            const Math::vec2 texture[3] = { mesh->GetTextureMeshes().begin()->second[i][0], mesh->GetTextureMeshes().begin()->second[i][1], mesh->GetTextureMeshes().begin()->second[i][2] };
            const Math::vec3 normal[3] = { mesh->GetNormals()[f[0]], mesh->GetNormals()[f[1]], mesh->GetNormals()[f[2]] };

            for (int j = 0; j < 3; ++j)
            {
                vb[index].m_position = position[j];
                vb[index].m_normal = normal[j];
                vb[index].m_texture0.Set(texture[j][0], texture[j][1], 0, 0);
                base_index.push_back(f[j]);
                index++;
            }
        }

        /// Smooth TBN
        std::vector<int> mask(vb.size());
        for (int i = 0; i < (int)vb.size(); i++)
        {
            Math::vec3 norm;
            for (int j = 0; j < (int)vb.size(); j++)
            {
                CurrentVertex* v = &vb[j];
                if (base_index[j] == i)
                {
                    norm += v->m_normal.XYZ();
                }
            }

            norm.Normalize();

            for (int j = 0; j < (int)vb.size(); j++)
            {
                CurrentVertex* v = &vb[j];
                if (base_index[j] == i)
                {
                    v->m_normal = norm;
                }
            }
        }

        _vb = new VertexArray<CurrentVertex>(vb);
        _ib = new IndexArray<unsigned>(ib);

        return true;
    }

    bool Cook(StaticGeometry* mesh, Graphics::IVertexArray* vb, Graphics::IIndexArray*& ib)
    {
        if (!mesh->GetVertices().empty() && !mesh->GetTextureMeshes().empty() && !mesh->GetNormals().empty())
            return CookPositionNormalTangentBitangentTexture0(mesh, vb, ib);
        else if (!mesh->GetVertices().empty() && !mesh->GetTextureMeshes().empty())
            return CookPositionTexture0(mesh, vb, ib);
        else if (!mesh->GetVertices().empty() && !mesh->GetNormals().empty())
            return CookPositionNormal(mesh, vb, ib);
        else if (!mesh->GetVertices().empty())
            return CookPosition(mesh, vb, ib);
        return false;
    }


    void StaticGeometry::GpuCache::Update(Graphics::IVideoDriver* driver)
    {
        if (!m_geom.GetCpuCache().IsOnCpu())
            m_geom.GetCpuCache().Update();

        Drop();
        Graphics::IVertexArray* vb = nullptr;
        Graphics::IIndexArray* ib = nullptr;
        if (!Cook(&m_geom, vb, ib))
            return;

        Graphics::ITrianglesUniquePtr mesh = Graphics::CreateTriangles(vb->GetVertexType(), driver);
        mesh->Cook(vb, ib);
        m_gpu_buffer = mesh.release();
    }

    Graphics::IRenderable* StaticGeometry::GpuCache::GetGpuBuffer()
    {
        return m_gpu_buffer;
    }

    StaticGeometry::CpuCache::CpuCache(StaticGeometry &value)
        : m_geom(value)
        , m_is_on_cpu(false)
    {}


    void StaticGeometry::CpuCache::SetVertices(const Vertices& value)
    {
        m_vertices = value;
        m_is_on_cpu = true;
        m_geom.m_bbox.Create(&m_vertices[0], m_vertices.size());
        m_geom.m_sphere.Create(&m_vertices[0], m_vertices.size());
    }

    void StaticGeometry::CpuCache::SetNormals(const Normals& value)
    {
        m_normals = value;
    }

    void StaticGeometry::CpuCache::SetFaces(const Faces& value)
    {
        m_faces = value;
    }

    void StaticGeometry::CpuCache::SetTextureMeshes(const TextureMeshes& value)
    {
        m_tex_coords = value;
    }

    const StaticGeometry::Vertices& StaticGeometry::CpuCache::GetVertices() const
    {
        return m_vertices;
    }

    const StaticGeometry::Normals& StaticGeometry::CpuCache::GetNormals() const
    {
        return m_normals;
    }

    const StaticGeometry::Faces& StaticGeometry::CpuCache::GetFaces() const
    {
        return m_faces;
    }

    const StaticGeometry::TextureMeshes& StaticGeometry::CpuCache::GetTextureMeshes() const
    {
        return m_tex_coords;
    }

    StaticGeometry::Vertices& StaticGeometry::CpuCache::GetVertices()
    {
        return m_vertices;
    }

    StaticGeometry::Normals& StaticGeometry::CpuCache::GetNormals()
    {
        return m_normals;
    }

    StaticGeometry::Faces& StaticGeometry::CpuCache::GetFaces()
    {
        return m_faces;
    }

    StaticGeometry::TextureMeshes& StaticGeometry::CpuCache::GetTextureMeshes()
    {
        return m_tex_coords;
    }

    bool StaticGeometry::CpuCache::IsOnCpu()
    {
        return m_is_on_cpu;
    }

    void StaticGeometry::CpuCache::Drop()
    {
        m_is_on_cpu = false;
        Vertices v;
        m_vertices.swap(v);
        Normals n;
        m_normals.swap(n);
        Faces f;
        m_faces.swap(f);
        TextureMeshes t;
        m_tex_coords.swap(t);
    }

    void StaticGeometry::CpuCache::Update(const Core::String &path)
    {
//        Drop();
//        StaticGeometry* geom = dynamic_cast<StaticGeometry*>(Utility::ParsePunkFile(path));
//        if (!geom)
//            return;
//        m_geom.SetVertices(geom->GetVertices());
//        m_geom.SetNormals(geom->GetNormals());
//        m_geom.SetFaces(geom->GetFaces());
//        m_geom.SetTextureMeshes(geom->GetTextureMeshes());
//        m_geom.SetWorldOffset(geom->GetWorldOffset());
//        m_is_on_cpu = true;
//        delete geom;
    }

    void StaticGeometry::CpuCache::Update()
    {
//        Drop();
//        StaticGeometry* geom = dynamic_cast<StaticGeometry*>(Utility::ParsePunkFile(System::Environment::Instance()->GetModelFolder() + m_geom.GetFilename()));
//        if (!geom)
//            return;
//        m_geom.SetVertices(geom->GetVertices());
//        m_geom.SetNormals(geom->GetNormals());
//        m_geom.SetFaces(geom->GetFaces());
//        m_geom.SetTextureMeshes(geom->GetTextureMeshes());
//        m_geom.SetWorldOffset(geom->GetWorldOffset());
//        m_is_on_cpu = true;
//        delete geom;
    }

    size_t StaticGeometry::CpuCache::GetCpuMemoryUsage() const
    {
        size_t res = 0;
        res += m_vertices.size() * sizeof(m_vertices[0]);
        res += m_normals.size() * sizeof(m_normals[0]);
        res += m_faces.size() * sizeof(m_faces[0]);
        for (auto i : m_tex_coords)
        {
            res += i.second.size() * sizeof(i.second[0]);
        }
        return res;
    }

    //    bool StaticGeometry::CpuCache::Save(std::ostream &stream) const
    //    {
    //        if (m_vertices.empty() || m_normals.empty() || m_faces.empty() || m_tex_coords.empty())
    //            throw System::PunkInvalidArgumentException(L"Can't save static geometry");

    //        int size = (int)m_vertices.size();
    //        stream.write((char*)&size, sizeof(size));
    //        stream.write((char*)&m_vertices[0], sizeof(m_vertices[0])*size);
    //        size = (int)m_faces.size();
    //        stream.write((char*)&size, sizeof(size));
    //        stream.write((char*)&m_faces[0], sizeof(m_faces[0])*size);
    //        size = (int)m_normals.size();
    //        stream.write((char*)&size, sizeof(size));
    //        stream.write((char*)&m_normals[0], sizeof(m_normals[0])*size);
    //        int count = (int)m_tex_coords.size();
    //        stream.write((char*)&count, sizeof(count));
    //        for (auto it = m_tex_coords.begin(); it != m_tex_coords.end(); ++it)
    //        {
    //            it->first.Save(stream);
    //            size = (int)it->second.size();
    //            stream.write((char*)&size, sizeof(size));
    //            stream.write((char*)&it->second[0], sizeof(it->second[0]) * size);
    //        }
    //        return true;
    //    }

    //    bool StaticGeometry::CpuCache::Load(std::istream &stream)
    //    {
    //        int size override;
    //        stream.read((char*)&size, sizeof(size));
    //        m_vertices.resize(size);
    //        stream.read((char*)&m_vertices[0], sizeof(m_vertices[0])*size);

    //        size override;
    //        stream.read((char*)&size, sizeof(size));
    //        m_faces.resize(size);
    //        stream.read((char*)&m_faces[0], sizeof(m_faces[0])*size);

    //        size override;
    //        stream.read((char*)&size, sizeof(size));
    //        m_normals.resize(size);
    //        stream.read((char*)&m_normals[0], sizeof(m_normals[0])*size);

    //        int count= 0;
    //        stream.read((char*)&count, sizeof(count));
    //        for (int i = 0; i < count; ++i)
    //        {
    //            Core::String name;
    //            name.Load(stream);
    //            size override;
    //            stream.read((char*)&size, sizeof(size));
    //            std::vector<Math::Vector4<Math::vec2>> v;
    //            v.resize(size);
    //            stream.read((char*)&v[0], sizeof(v[0]) * size);
    //            m_tex_coords[name] = v;
    //        }
    //        m_is_on_cpu = true;
    //        return true;
    //    }

    StaticGeometry::StaticGeometry()
        : m_cpu_cache(*this)
        , m_gpu_cache(*this)
    {
    }

    StaticGeometry::~StaticGeometry()
    {
    }

    //    bool StaticGeometry::Save(std::ostream& stream) const
    //    {
    //        Geometry::Save(stream);
    //        m_bbox.Save(stream);
    //        return m_cpu_cache.Save(stream);
    //    }

    //    bool StaticGeometry::Load(std::istream& stream)
    //    {
    //        Geometry::Load(stream);
    //        m_bbox.Load(stream);
    //        return m_cpu_cache.Load(stream);
    //    }

    StaticGeometry::Vertices& StaticGeometry::GetVertexArray()
    {
        return m_cpu_cache.GetVertices();
    }

    StaticGeometry::Normals& StaticGeometry::GetNormalArray()
    {
        return m_cpu_cache.GetNormals();
    }

    StaticGeometry::Faces& StaticGeometry::GetFaceArray()
    {
        return m_cpu_cache.GetFaces();
    }

    const StaticGeometry::Vertices& StaticGeometry::GetVertexArray() const
    {
        return m_cpu_cache.GetVertices();
    }

    const StaticGeometry::Normals& StaticGeometry::GetNormalArray() const
    {
        return m_cpu_cache.GetNormals();
    }

    const StaticGeometry::Faces& StaticGeometry::GetFaceArray() const
    {
        return m_cpu_cache.GetFaces();
    }

    void StaticGeometry::SetVertices(const StaticGeometry::Vertices& value)
    {
        m_cpu_cache.SetVertices(value);
    }

    void StaticGeometry::SetNormals(const Normals& value)
    {
        m_cpu_cache.SetNormals(value);
    }

    void StaticGeometry::SetFaces(const StaticGeometry::Faces& value)
    {
        m_cpu_cache.SetFaces(value);
    }

    void StaticGeometry::SetTextureMeshes(const StaticGeometry::TextureMeshes& value)
    {
        m_cpu_cache.SetTextureMeshes(value);
    }

    const StaticGeometry::Vertices& StaticGeometry::GetVertices() const
    {
        return m_cpu_cache.GetVertices();
    }

    const StaticGeometry::Normals& StaticGeometry::GetNormals() const
    {
        return m_cpu_cache.GetNormals();
    }

    const StaticGeometry::Faces& StaticGeometry::GetFaces() const
    {
        return m_cpu_cache.GetFaces();
    }

    const StaticGeometry::TextureMeshes& StaticGeometry::GetTextureMeshes()
    {
        return m_cpu_cache.GetTextureMeshes();
    }

    void StaticGeometry::SetWorldOffset(const Math::mat4& value)
    {
        m_world_offset = value;
    }

    const Math::mat4& StaticGeometry::GetWorldOffset() const
    {
        return m_world_offset;
    }

    void StaticGeometry::SetFilename(const Core::String& filename)
    {
        m_filename = filename;
    }

    const Core::String& StaticGeometry::GetFilename() const
    {
        return m_filename;
    }

    StaticGeometry::GpuCache& StaticGeometry::GetGpuCache()
    {
        return m_gpu_cache;
    }

    StaticGeometry::CpuCache& StaticGeometry::GetCpuCache()
    {
        return m_cpu_cache;
    }

    void StaticGeometry::SetName(const Core::String& value)
    {
        m_name = value;
    }

    const Core::String& StaticGeometry::GetName() const
    {
        return m_name;
    }
}
PUNK_ENGINE_END

