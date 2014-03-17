#include "gl_video_driver.h"
#include "gl_settings.h"
#include "gl_capabilities.h"

PUNK_ENGINE_BEGIN
namespace Graphics {
    namespace OpenGL {
        GlVideoDriverSettings::GlVideoDriverSettings(GlVideoDriver* driver)
            : m_driver(driver)
        {}

        GlVideoDriverSettings::~GlVideoDriverSettings() {}

        void GlVideoDriverSettings::EnableMultisampling(bool value) {
            IsMultisamplingEnabled = value && IsMultisamplingSupported(m_driver);
        }

        bool GlVideoDriverSettings::IsEnabledMultisampling() const {
            return IsMultisamplingEnabled;
        }
        void GlVideoDriverSettings::EnableCoverageSampling(bool value) {
            IsCoverageSamplingEnabled = value && IsCoverageSamplingSupported(m_driver);
        }

        bool GlVideoDriverSettings::IsEnabledCoverageSampling() const {
            return IsCoverageSamplingEnabled;
        }

        void GlVideoDriverSettings::SetShadowMapSize(std::uint32_t value) {
            ShadowMapSize = value;
        }

        std::uint32_t GlVideoDriverSettings::GetShadowMapSize() const {
            return ShadowMapSize;
        }

        std::uint32_t GlVideoDriverSettings::GetFrameBufferConfigCount() const {
            return m_fb_config.size();
        }

        const FrameBufferConfig& GlVideoDriverSettings::GetFrameBufferConfig(std::uint32_t i) {
            return m_fb_config.at(i);
        }

        void GlVideoDriverSettings::Load() {
            GetFrameBufferConfigs(m_fb_config, m_driver);
        }

        void GlVideoDriverSettings::Save() {

        }

        void GlVideoDriverSettings::Apply() {

        }
    }
}
PUNK_ENGINE_END
