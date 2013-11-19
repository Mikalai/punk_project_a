#ifndef GL_CAPABILITIES_H
#define GL_CAPABILITIES_H

#include <vector>
#include "gpu/common/frame_buffer/frame_buffer_config.h"
#include "gpu/common/frame_buffer/render_buffer_config.h"

namespace Gpu
{
    namespace OpenGL
    {
        class GlVideoDriverProxy;

        bool IsMultisamplingSupported(GlVideoDriverProxy* driver);
        bool IsCoverageSamplingSupported(GlVideoDriverProxy* driver);
        bool IsShaderIncludeSupported(GlVideoDriverProxy* driver);
        int GetMaxMultisampleDepth(GlVideoDriverProxy* driver);
        int GetCoverageSampleConfigsCount(GlVideoDriverProxy* driver);
        void GetCoverageConfigs(std::vector<int>& value, GlVideoDriverProxy* driver);
        void GetFrameBufferConfigs(std::vector<FrameBufferConfig>& value, GlVideoDriverProxy* driver);
        void GetColorBufferConfigs(std::vector<RenderBufferConfig>& value, GlVideoDriverProxy* driver);
        void GetDepthBufferConfigs(std::vector<RenderBufferConfig>& value, GlVideoDriverProxy* driver);
    }
}

#endif // GL_CAPABILITIES_H
