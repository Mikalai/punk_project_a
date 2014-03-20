#ifndef _H_PUNK_GPU_OPENGL_RENDERABLE_BUILDER
#define _H_PUNK_GPU_OPENGL_RENDERABLE_BUILDER

#include <vector>
#include <graphics/renderable/renderable_builder.h>
#include <math/vec4.h>
#include <graphics/opengl/module.h>

PUNK_ENGINE_BEGIN
namespace Graphics {
    namespace OpenGL {
        //class Frame;

        class GlRenderableBuilder : public RenderableBuilder
        {
        public:
            GlRenderableBuilder(IVideoDriver* driver);
            virtual ~GlRenderableBuilder();

            void Begin(const PrimitiveType& value) override;
            IRenderable* ToRenderable() override;
            void End() override;

        private:

            IRenderable* BuildVertexBufferP(const std::vector<Math::vec4>& position);
            IRenderable* BuildVertexBufferPC(const std::vector<Math::vec4>& position, const std::vector<Math::vec4>& color);
            IRenderable* BuildVertexBufferPT(const std::vector<Math::vec4>& position, const std::vector<Math::vec4>& texcoord);
            IRenderable* BuildVertexBufferPTC(const std::vector<Math::vec4>& position, const std::vector<Math::vec4>& texcoord, const std::vector<Math::vec4>& color);
            IRenderable* BuildVertexBufferPN(const std::vector<Math::vec4>& position, const std::vector<Math::vec4>& normal);
            IRenderable* BuildVertexBufferPNT0(const std::vector<Math::vec4>& position, const std::vector<Math::vec4>& normal, const std::vector<Math::vec4>& texcoord);
        };
    }
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_GPU_OPENGL_RENDERABLE_BUILDER
