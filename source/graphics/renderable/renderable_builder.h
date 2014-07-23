#ifndef _H_PUNK_GPU_RENDERABLE_BUILDER
#define _H_PUNK_GPU_RENDERABLE_BUILDER

#include <vector>
#include <graphics/primitives/renderable.h>
#include "irenderable_builder.h"

PUNK_ENGINE_BEGIN
namespace Graphics {

    class PUNK_ENGINE_LOCAL RenderableBuilder : public IRenderableBuilder {
	public:
        RenderableBuilder();
        RenderableBuilder(const RenderableBuilder&) = delete;
        RenderableBuilder& operator = (const RenderableBuilder&) = delete;
        virtual ~RenderableBuilder();
		
		void Initialize(IVideoDriver* driver) override;
        void Vertex3f(float x, float y, float z) override;
        void Vertex3fv(const float* value) override;
        void Vertex3fv(const Math::vec3& value) override;
        void Color3f(float r, float g, float b) override;
        void Color3fv(const float* value) override;
        void Color3fv(const Math::vec3& value) override;
        void TexCoord2f(float x, float y) override;
        void TexCoord2fv(const float* value) override;
        void TexCoord2fv(const Math::vec2& value) override;
        void Normal3f(float x, float y, float z) override;
        void Normal3fv(const float* value) override;
        void Normal3fv(const Math::vec3& value) override;
        const Math::BoundingSphere* GetBoundingSphere() const override;
        bool IsValid() const override;

    protected:

		void Clear();
        void ValidateBegin();
        void ValidateEnd();
        void ValidateDraw();

        IVideoDriver* m_driver {nullptr};

        std::vector<Math::point4d> m_vertex;
        std::vector<Math::vec4> m_color;
        std::vector<Math::vec4> m_normal;
        std::vector<Math::point4d> m_texcoord;

        bool m_begin_active {false};

        PrimitiveType m_primitive_type;
        PrimitiveType m_high_level_type;

        mutable Math::BoundingSphere* m_bsphere {nullptr};		
	};
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_GPU_RENDERABLE_BUILDER
