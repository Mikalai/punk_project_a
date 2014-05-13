//#ifndef _H_PUNK_VIRTUAL_SKIN_GEOMETRY
//#define _H_PUNK_VIRTUAL_SKIN_GEOMETRY
//
//#include <vector>
//#include <map>
//
//#include <array>
//#include <string/string.h>
//#include <math/bounding_box.h>
//#include "geometry.h"
//
//PUNK_ENGINE_BEGIN
//namespace Graphics {
//    class IVideoDriver;
//    class IRenderable;
//}
//
//namespace Attributes {
//    class Armature;
//    class ArmatureAnimationMixer;
//
//    class PUNK_ENGINE_API SkinGeometry : public Geometry
//	{
//	public:		
//		typedef std::map<int, std::map<Core::String, float>> BoneWeights;
//        typedef std::map<Core::String, std::vector<std::array<Math::vec2, 4>>> TextureMeshes;
//
//	public:
//
//        struct GpuCache
//        {
//            GpuCache(SkinGeometry& value);
//            ~GpuCache();
//            bool IsOnGpu();
//            void Drop();
//            void Update(Armature* armature, Graphics::IVideoDriver* driver);
//            Graphics::IRenderable* GetGpuBuffer();
//            size_t GetGpuMemoryUsage() const;
//        private:
//            SkinGeometry& m_geom;
//            Graphics::IRenderable* m_gpu_buffer;
//        };
//
//        struct CpuCache
//        {
//            CpuCache(SkinGeometry& value);
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
//            void SetBoneWeights(const BoneWeights& value);
//
//            const Vertices& GetVertices() const;
//            const Normals& GetNormals() const;
//            const Faces& GetFaces() const;
//            const TextureMeshes& GetTextureMeshes() const;
//            const BoneWeights& GetBoneWeights() const;
//
//            Vertices& GetVertices();
//            Normals& GetNormals();
//            Faces& GetFaces();
//            TextureMeshes& GetTextureMeshes();
//            BoneWeights& GetBoneWeights();
//
//            void Save(Core::Buffer *buffer) const;
//            void Load(Core::Buffer *buffer);
//        private:
//            SkinGeometry& m_geom;
//            Vertices m_vertices;
//            Normals m_normals;
//            Faces m_faces;
//            TextureMeshes m_tex_coords;
//            BoneWeights m_bone_weights;
//            bool m_is_on_cpu;
//        };
//
//
//    public:
//		SkinGeometry();
//        SkinGeometry(const SkinGeometry&) = delete;
//        SkinGeometry& operator = (const SkinGeometry&) = delete;
//        virtual ~SkinGeometry();
//
//        virtual Vertices& GetVertexArray() override;
//        virtual Normals& GetNormalArray() override;
//        virtual Faces& GetFaceArray() override;
//        virtual const Vertices& GetVertexArray() const override;
//        virtual const Normals& GetNormalArray() const override;
//        virtual const Faces& GetFaceArray() const override;
//
//        void SetVertices(const Vertices& value);
//        void SetNormals(const Normals& value);
//        void SetFaces(const Faces& value);
//        void SetTextureMeshes(const TextureMeshes& value);
//        void SetBoneWeights(const BoneWeights& value);
//
//        const Vertices& GetVertices() const;
//        const Normals& GetNormals() const;
//        const Faces& GetFaces() const;
//        const TextureMeshes& GetTextureMeshes() const;
//        const BoneWeights& GetBoneWeights() const;
//
//        void SetWorldOffset(const Math::mat4& value);
//        const Math::mat4& GetWorldOffset() const;
//
//        void SetFilename(const Core::String& filename);
//        const Core::String& GetFilename() const;
//
//        GpuCache& GetGpuCache();
//        CpuCache& GetCpuCache();
//
//        void SetArmatureName(const Core::String& name);
//        const Core::String& GetArmatureName() const;
//
//        void SetName(const Core::String& value);
//        const Core::String& GetName() const;
//
//    private:
//
//        Core::String m_armature_name;
//        Core::String m_filename;
//        Core::String m_name;
//
//        Math::mat4 m_world_offset;
//
//        CpuCache m_cpu_cache;
//        GpuCache m_gpu_cache;
//
//        friend class CpuCache;
//        friend class GpuCache;
//
//        PUNK_OBJECT(SkinGeometry)        
//	};
//}
//PUNK_ENGINE_END
//
//#endif	//	_H_PUNK_VIRTUAL_SKIN_GEOMETRY
