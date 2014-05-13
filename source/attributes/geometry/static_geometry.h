//#ifndef _H_PUNK_VIRTUAL_STATIC_GEOMETRY
//#define _H_PUNK_VIRTUAL_STATIC_GEOMETRY
//
//#include <array>
//#include <vector>
//#include <map>
//
//#include <math/bounding_box.h>
//#include <math/vec2.h>
//#include "geometry.h"
//
//PUNK_ENGINE_BEGIN
//namespace Graphics {
//    class IVideoDriver;
//    class IRenderable;
//}
//
//namespace Attributes {
//
//    class PUNK_ENGINE_API StaticGeometry : public Geometry {
//    public:
//        typedef std::map<Core::String, std::vector<std::array<Math::vec2, 4>>> TextureMeshes;
//
//    /*    struct GpuCache
//        {
//            GpuCache(StaticGeometry& value);
//            ~GpuCache();
//            bool IsOnGpu();
//            void Drop();
//            void Update(Graphics::IVideoDriver* driver);
//            Graphics::IRenderable* GetGpuBuffer();
//            size_t GetGpuMemoryUsage() const;
//        private:
//            StaticGeometry& m_geom;
//            Graphics::IRenderable* m_gpu_buffer;
//        };*/
//
//        struct CpuCache
//        {
//            CpuCache(StaticGeometry& value);
//            bool IsOnCpu();
//            void Drop();
//            void Update();
//            void Update(const Core::String& path);
//            size_t GetCpuMemoryUsage() const;
//
//            void SetVertices(const Vertices& value);
//            void SetNormals(const Normals& value);
//            void SetFaces(const Faces& value);
//            void SetTextureMeshes(const TextureMeshes& value);
//
//            const Vertices& GetVertices() const;
//            const Normals& GetNormals() const;
//            const Faces& GetFaces() const;
//            const TextureMeshes& GetTextureMeshes() const;
//
//            Vertices& GetVertices();
//            Normals& GetNormals();
//            Faces& GetFaces();
//            TextureMeshes& GetTextureMeshes();
//
////            bool Save(std::ostream &stream) const;
////            bool Load(std::istream &stream);
//
//        private:
//            StaticGeometry& m_geom;
//            Vertices m_vertices;
//            Normals m_normals;
//            Faces m_faces;
//            TextureMeshes m_tex_coords;
//            bool m_is_on_cpu;
//        };
//
//    public:
//
//        StaticGeometry();
//        virtual ~StaticGeometry();
//
//		//	geometry stuff
//		virtual Vertices& GetVerticesPosition() override;
//		virtual Normals& GetVerticesNormals() override;
//		virtual Faces& GetFaces() override;
//		virtual const Vertices& GetVerticesPosition() const override;
//		virtual const Normals& GetVerticesNormals() const override;
//		virtual const Faces& GetFaces() const override;
//
//		//	graphics stuff
//		virtual std::uint64_t GetVertexType() const override;
//		virtual Graphics::IVertexArray* GetVertexArray() const override;
//		virtual Graphics::IIndexArray* GetIndexArray() const override;
//		virtual bool IsIndexedMesh() const override;
//
//        void SetVertices(const Vertices& value);
//        void SetNormals(const Normals& value);
//        void SetFaces(const Faces& value);
//        void SetTextureMeshes(const TextureMeshes& value);
//
//        const Vertices& GetVertices() const;
//        const Normals& GetNormals() const;
//        const Faces& GetFaces() const;
//        const TextureMeshes& GetTextureMeshes();
//
//        void SetWorldOffset(const Math::mat4& value);
//        const Math::mat4& GetWorldOffset() const;
//
//        void SetFilename(const Core::String& filename);
//        const Core::String& GetFilename() const;
//
//        //GpuCache& GetGpuCache();
//        CpuCache& GetCpuCache();
//
//        void SetName(const Core::String& value);
//        const Core::String& GetName() const;
//
//    private:
//
//        Core::String m_name;
//        Core::String m_filename;
//        Math::mat4 m_world_offset;
//
//        CpuCache m_cpu_cache;
//        //GpuCache m_gpu_cache;
//
//        friend class CpuCache;
//       // friend class GpuCache;
//
//		std::uint64_t m_vertex_type{ 0 };
//		Graphics::IVertexArray* m_vertex_array{ nullptr };
//		Graphics::IIndexArray* m_index_array{ nullptr };
//
//        PUNK_OBJECT(StaticGeometry)
//    };
//}
//PUNK_ENGINE_END
//
//#endif
