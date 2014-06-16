#include <string.h>
#include <system/logger/module.h>
#include <graphics/opengl/module.h>
#include <graphics/video_driver/gl_video_driver/module.h>
#include <graphics/frame_buffer/gl_frame_buffer/module.h>

PUNK_ENGINE_BEGIN
namespace Graphics {
    namespace OpenGL {

        bool IsSupported(const char* value, GlVideoDriver* driver)
        {            
#ifdef __gnu_linux__
            {
                const char* str = glXQueryExtensionsString(driver->GetDisplay(), XDefaultScreen(driver->GetDisplay()));
                bool res = driver->IsExtensionSupported(value, str);
                if (res)
                    return res;
            }
            GLint count;
            glGetIntegerv(GL_NUM_EXTENSIONS, &count);
            for (GLint i = 0; i != count; ++i)
            {
                const char* ext = (const char*)glGetStringi(GL_EXTENSIONS, i);
                if (!strcmp(value, ext))
                    return true;
            }
            return false;
#elif defined _WIN32
            GLint count;
            glGetIntegerv(GL_NUM_EXTENSIONS, &count);
            for (GLint i = 0; i != count; ++i)
            {
                const char* ext = (const char*)glGetStringi(GL_EXTENSIONS, i);
                if (!strcmp(value, ext))
                    return true;
            }
            return false;
#endif
        }

        bool IsMultisamplingSupported(GlVideoDriver *driver)
        {
            return IsSupported("GL_EXT_framebuffer_blit", driver) && IsSupported("GL_EXT_framebuffer_multisample", driver);
        }

        bool IsCoverageSamplingSupported(GlVideoDriver *driver)
        {
            return IsSupported("GL_NV_framebuffer_multisample_coverage", driver);
        }

        bool IsShaderIncludeSupported(GlVideoDriver *driver)
        {
            return IsSupported("GL_ARB_shading_language_include", driver);
        }

        int GetMaxMultisampleDepth(GlVideoDriver* driver)
        {
            if (!IsMultisamplingSupported(driver))
                return 0;
            GLint value;
            GL_CALL(glGetIntegerv(GL_MAX_SAMPLES_EXT, &value));
            return value;
        }

        int GetCoverageSampleConfigsCount(GlVideoDriver* driver)
        {
            if (!IsMultisamplingSupported(driver))
                return 0;
            if (!IsCoverageSamplingSupported(driver))
                return 0;
            GLint value;
            GL_CALL(glGetIntegerv(GL_MAX_MULTISAMPLE_COVERAGE_MODES_NV, &value));
            return value;
        }

        void GetCoverageConfigs(std::vector<int>& value, GlVideoDriver* driver)
        {
            int count = GetCoverageSampleConfigsCount(driver);
            if (count == 0)
                return;
            value.resize(2*count+4);
            GL_CALL(glGetIntegerv(GL_MULTISAMPLE_COVERAGE_MODES_NV, &value[0]));
        }

        void GetFrameBufferConfigs(std::vector<FrameBufferConfig> &value, GlVideoDriver *driver)
        {
            std::vector<RenderBufferConfig> color_configs;
            GetColorBufferConfigs(color_configs, driver);

            std::vector<RenderBufferConfig> depth_configs;
            GetDepthBufferConfigs(depth_configs, driver);

            std::vector<int> coverage_configs;
            GetCoverageConfigs(coverage_configs, driver);

            for (RenderBufferConfig& color_config : color_configs)
            {
                for (RenderBufferConfig& depth_config : depth_configs)
                {
                    FrameBufferConfig fb_config;
                    Core::String root = color_config.Name() + " " + depth_config.Name();					
                    fb_config.Name(root);
                    fb_config.ColorFormat(color_config.Format());
                    fb_config.DepthFormat(depth_config.Format());
                    fb_config.RedBitsCount(color_config.Bits());
                    fb_config.DepthBitsCount(depth_config.Bits());
                    fb_config.CoverageSamples(0);
                    fb_config.DepthSamples(0);

                    try
                    {
						System::GetDefaultLogger()->Info("Check frame buffer config " + fb_config.Name());
                        GlFrameBuffer frame_buffer(driver);
                        frame_buffer.Config(fb_config);
                        value.push_back(fb_config);
                    }
                    catch(System::Error::SystemException& e)
                    {
                        System::GetDefaultLogger()->Error(e.Message());
                    }

                    if (!coverage_configs.empty())
                    {
                        GLint max_sample = GetCoverageSampleConfigsCount(driver);
                        for (int coverage_index = 0; coverage_index < max_sample; ++coverage_index)
                        {
                            fb_config.DepthSamples(coverage_configs[2*coverage_index + 1]);
                            fb_config.CoverageSamples(coverage_configs[2*coverage_index]);

                            if (fb_config.DepthSamples() == fb_config.CoverageSamples())
                            {
                                fb_config.Name(root + Core::String(L" - {0} MSAA").arg(fb_config.DepthSamples()));
                            }
                            else
                            {
                                fb_config.Name(root + Core::String(L" - {0}/{1} CSAA").arg(fb_config.CoverageSamples()).arg(fb_config.DepthSamples()));
                            }

                            try
                            {
								System::GetDefaultLogger()->Info("Check frame buffer config " + fb_config.Name());
                                GlFrameBuffer frame_buffer(driver);
                                frame_buffer.Config(fb_config);
                                value.push_back(fb_config);
                            }
                            catch(...)
                            {}
                        }
                    }
                    else
                    {
                        for (int sample_index = 1, max_samples = GetMaxMultisampleDepth(driver); sample_index <= max_samples; ++sample_index)
                        {
                            fb_config.DepthSamples(sample_index);
                            fb_config.Name(root + Core::String(L" - {0} MSAA").arg(fb_config.DepthSamples()));

                            try
                            {
								System::GetDefaultLogger()->Info("Check frame buffer config " + fb_config.Name());
                                GlFrameBuffer frame_buffer(driver);
                                frame_buffer.Config(fb_config);

                                if (fb_config.DepthSamples() > sample_index)
                                    sample_index = fb_config.DepthSamples();

                                value.push_back(fb_config);
                            }
                            catch(...)
                            {}
                        }
                    }

                }
            }
        }

        void GetColorBufferConfigs(std::vector<RenderBufferConfig>& value, GlVideoDriver* driver)
        {
            RenderBufferConfig config;
            config.Name("RGBA8");
            config.Bits(8);
            config.Format(ImageModule::ImageFormat::RGBA8);
            value.push_back(config);

            config.Name("RGB10_A2");
            config.Bits(10);
            config.Format(ImageModule::ImageFormat::RGB10_A2);
            value.push_back(config);

            if (IsSupported("GL_EXT_texture_sRGB", driver) && IsSupported("GL_EXT_framebuffer_sRGB", driver))
            {
                config.Name("sRGB8_A8");
                config.Bits(8);
                config.Format(ImageModule::ImageFormat::SRGB8_ALPHA8);
                value.push_back(config);
            }

            if (IsSupported("GL_ARB_texture_float", driver))
            {
                config.Name("RGBA16F");
                config.Bits(16);
                config.Format(ImageModule::ImageFormat::RGBA16F);
                value.push_back(config);

                config.Name("RGBA32F");
                config.Bits(32);
                config.Format(ImageModule::ImageFormat::RGBA32F);
                value.push_back(config);
            }

            if (IsSupported("GL_EXT_packed_float", driver))
            {
                config.Name("RG11F_B10F");
                config.Bits(11);
                config.Format(ImageModule::ImageFormat::R11F_G11F_B10F);
                value.push_back(config);
            }
        }

        void GetDepthBufferConfigs(std::vector<RenderBufferConfig>& value, GlVideoDriver* driver)
        {
            RenderBufferConfig config;
            config.Name("D24");
            config.Bits(24);
            config.Format(ImageModule::ImageFormat::DEPTH_COMPONENT24);
            value.push_back(config);

            if (IsSupported("GL_NV_depth_buffer_float", driver))
            {
                config.Name("D32F");
                config.Bits(32);
                config.Format(ImageModule::ImageFormat::DEPTH_COMPONENT32F);
                value.push_back(config);
            }
        }
    }
}
PUNK_ENGINE_END
