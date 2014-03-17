#ifndef GL_CAPABILITIES_H
#define GL_CAPABILITIES_H

#include <config.h>
#include <vector>
#include <graphics/frame_buffer/module.h>

PUNK_ENGINE_BEGIN
namespace Graphics {
    namespace OpenGL {

        class GlVideoDriver;

        bool IsMultisamplingSupported(GlVideoDriver* driver);
        bool IsCoverageSamplingSupported(GlVideoDriver* driver);
        bool IsShaderIncludeSupported(GlVideoDriver* driver);
        int GetMaxMultisampleDepth(GlVideoDriver* driver);
        int GetCoverageSampleConfigsCount(GlVideoDriver* driver);
        void GetCoverageConfigs(std::vector<int>& value, GlVideoDriver* driver);
        void GetFrameBufferConfigs(std::vector<FrameBufferConfig>& value, GlVideoDriver* driver);
        void GetColorBufferConfigs(std::vector<RenderBufferConfig>& value, GlVideoDriver* driver);
        void GetDepthBufferConfigs(std::vector<RenderBufferConfig>& value, GlVideoDriver* driver);
    }
}
PUNK_ENGINE_END

#endif // GL_CAPABILITIES_H
