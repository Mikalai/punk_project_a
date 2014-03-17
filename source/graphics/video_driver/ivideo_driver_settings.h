#ifndef VIDEO_DRIVER_SETTINGS_H
#define VIDEO_DRIVER_SETTINGS_H

#include <cstdint>
#include <config.h>

PUNK_ENGINE_BEGIN
namespace Graphics {
    class FrameBufferConfig;

    class IVideoDriverSettings {
    public:
        virtual void EnableMultisampling(bool value) = 0;
        virtual bool IsEnabledMultisampling() const = 0;
        virtual void EnableCoverageSampling(bool value) = 0;
        virtual bool IsEnabledCoverageSampling() const = 0;
        virtual void SetShadowMapSize(std::uint32_t value) = 0;
        virtual std::uint32_t GetShadowMapSize() const = 0;
        virtual std::uint32_t GetFrameBufferConfigCount() const = 0;
        virtual const FrameBufferConfig& GetFrameBufferConfig(std::uint32_t i) = 0;
        virtual void Load() = 0;
        virtual void Save() = 0;
        virtual void Apply() = 0;
    };
}
PUNK_ENGINE_END

#endif // VIDEO_DRIVER_CAPS_H
