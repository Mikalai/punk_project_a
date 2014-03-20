#ifndef FS_TEXT_SOLID_H
#define FS_TEXT_SOLID_H

#include <graphics/shaders/gl_shaders/gl_shader.h>

PUNK_ENGINE_BEGIN
namespace Graphics
{
    namespace OpenGL
    {
        class FsTextSolid : public Shader
        {
        public:
            FsTextSolid();
            void InitUniforms() override;
            void BindParameters(const CoreState& params) override;
            int64_t GetRequiredAttributesSet() const override;

        private:
            unsigned uDiffuseColor;
            unsigned uTextMap;
        };
    }
}
PUNK_ENGINE_END

#endif // FS_TEXT_SOLID_H
