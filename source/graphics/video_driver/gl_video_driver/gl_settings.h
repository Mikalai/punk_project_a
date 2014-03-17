#ifndef GL_SETTINGS_H
#define GL_SETTINGS_H

#include <vector>
#include <config.h>
#include <graphics/frame_buffer/module.h>
#include <graphics/video_driver/ivideo_driver_settings.h>

PUNK_ENGINE_BEGIN
namespace Graphics {
    namespace OpenGL {
        class GlVideoDriver;

        class PUNK_ENGINE_LOCAL GlVideoDriverSettings : public IVideoDriverSettings
        {
        public:
            GlVideoDriverSettings(GlVideoDriver* driver);
            virtual ~GlVideoDriverSettings();
            void EnableMultisampling(bool value) override;
            bool IsEnabledMultisampling() const override;
            void EnableCoverageSampling(bool value) override;
            bool IsEnabledCoverageSampling() const override;
            void SetShadowMapSize(std::uint32_t value) override;
            std::uint32_t GetShadowMapSize() const override;
            std::uint32_t GetFrameBufferConfigCount() const override;
            const FrameBufferConfig& GetFrameBufferConfig(std::uint32_t i) override;
            void Load() override;
            void Save() override;
            void Apply() override;
        private:
            GlVideoDriver* m_driver {nullptr};
            bool IsMultisamplingEnabled {false};
            bool IsCoverageSamplingEnabled {false};
            unsigned ShadowMapSize {512};
            std::vector<FrameBufferConfig> m_fb_config;
        };
    }
}
PUNK_ENGINE_END

#endif // GL_SETTINGS_H
