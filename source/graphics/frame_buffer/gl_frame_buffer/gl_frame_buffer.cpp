#include <math/vec4.h>
#include <core/ifactory.h>
#include <graphics/video_driver/gl_video_driver/module.h>
#include <graphics/frame_buffer/frame_buffer_config.h>
#include <graphics/texture/gl_texture/module.h>
#include "gl_frame_buffer_convert.h"
#include "gl_color_render_buffer.h"
#include "gl_depth_render_buffer.h"
#include "gl_frame_buffer.h"

PUNK_ENGINE_BEGIN
namespace Graphics
{
    static int count = 0;
    namespace OpenGL
    {
        GlFrameBuffer GlFrameBuffer::Backbuffer{nullptr};

        GlFrameBuffer::GlFrameBuffer(IVideoDriver *driver)
            : FrameBuffer(driver)
            , m_color_rb(nullptr)
            , m_depth_rb(nullptr)
            , m_resolve_rb(nullptr)
            , m_fb(0)
        {
            count++;
            if (driver) {
                GL_CALL(glGenFramebuffers(1, &m_fb));
            }
        }

        void GlFrameBuffer::Config(const FrameBufferConfig& config) {
            Graphics::FrameBuffer::Config(config);
            Clear();

            count++;
            GL_CALL(glGenFramebuffers(1, &m_fb));

			m_color_texture.reset(Core::CreateInstance<ITexture2D>(IID_ITexture2D));
			if (m_color_texture.get()) {
				m_color_texture->Initialize(config.Width(),
					config.Height(),
					config.ColorFormat(),
					ImageModule::ImageFormat::RGBA, ImageModule::DataType::Float, 0, true, GetVideoDriver());
			}

            if (GetVideoDriver()->GetSettings()->IsEnabledMultisampling()) {
                m_resolve_rb = new GlFrameBuffer(GetVideoDriver());
                m_resolve_rb->AttachColorTarget(0, m_color_texture.get());

                //  Bind();
                m_color_rb = new GlColorRenderBuffer(config, GetVideoDriver());
                AttachColorTarget(0, m_color_rb);

                //   Bind();
                m_depth_rb = new GlDepthRenderBuffer(config, GetVideoDriver());
                AttachDepthTarget(m_depth_rb);
            }
            else {
				m_depth_texture.reset(Core::CreateInstance<ITexture2D>(IID_ITexture2D));
				if (m_depth_texture.get()) {
					m_depth_texture->Initialize(
						config.Width(),
						config.Height(),
						config.DepthFormat(),
						ImageModule::ImageFormat::DepthComponent, ImageModule::DataType::Float, 0, false,
						GetVideoDriver());
				}
                AttachColorTarget(0, m_color_texture.get());
                AttachDepthTarget(m_depth_texture.get());
            }
            Bind();
            Check();
            Unbind();

            CheckConfigCompatibility();
        }

        void GlFrameBuffer::CheckConfigCompatibility()
        {
            //  next code is deprecated in gl 3.3
            //            Bind();
            //            GLint value;
            //            GL_CALL(glGetIntegerv(GL_RED_BITS, &value));
            //            if (value != Config()->RedBitsCount())
            //                throw System::PunkException(L"Failed to create frame buffer with " + Config()->Name() + L" config");

            //            GL_CALL(glGetIntegerv(GL_DEPTH_BITS, &value));
            //            if (value != Config()->DepthBitsCount())
            //                throw System::PunkException(L"Failed to create frame buffer with " + Config()->Name() + L" config");

            //            if (GetVideoDriver()->IsMultisamplingEnabled())
            //            {
            //                m_resolve_rb->Bind();
            //                GL_CALL(glGetIntegerv(GL_RED_BITS, &value));
            //                if (value != Config()->RedBitsCount())
            //                    throw System::PunkException(L"Failed to create frame buffer with " + Config()->Name() + L" config");
            //                m_resolve_rb->Unbind();
            //            }
            //            Unbind();
        }

        GlFrameBuffer::~GlFrameBuffer()
        {
            Destroy();
        }

        void GlFrameBuffer::SetClearFlag(bool color, bool depth, bool stencil) {
            m_clear_color = color;
            m_clear_depth = depth;
            m_clear_stencil = stencil;
        }

        void GlFrameBuffer::Clear()
        {
            GLenum flag = 0;
            if (m_clear_color)
                flag |= GL_COLOR_BUFFER_BIT;
            if (m_clear_depth)
                flag |= GL_DEPTH_BUFFER_BIT;
            if (m_clear_stencil)
                flag |= GL_STENCIL_BUFFER_BIT;
            GL_CALL(glClearDepth(1));
            GL_CALL(glClear(flag));
        }

        void GlFrameBuffer::Destroy()
        {
            if (m_color_rb)
            {
                delete m_color_rb;
                m_color_rb = nullptr;
            }
            if (m_depth_rb)
            {
                delete m_depth_rb;
                m_depth_rb = nullptr;
            }
            if (m_resolve_rb)
            {
                delete m_resolve_rb;
                m_resolve_rb = nullptr;
            }
            if (m_fb)
            {
                GL_CALL(glDeleteFramebuffers(1, &m_fb));
                count--;
                m_fb = 0;
            }
        }

        void GlFrameBuffer::SetClearColor(float r, float g, float b, float a) {
            GL_CALL(glClearColor(r, g, b, a));
        }

        void GlFrameBuffer::SetClearColor(const Math::vec4& color)
        {
            GL_CALL(glClearColor(color[0], color[1], color[2], color[3]));
        }

        void GlFrameBuffer::SetClearDepth(float value)
        {
            GL_CALL(glClearDepth(value));
        }

        void GlFrameBuffer::Bind()
        {
            GL_CALL(glGetIntegerv(GL_FRAMEBUFFER_BINDING, (GLint*)&m_prev_fb));
            if (m_prev_fb != m_fb)
            {
                GL_CALL(glBindFramebuffer(GL_FRAMEBUFFER, m_fb));
            }
        }

        void GlFrameBuffer::Unbind()
        {
            GL_CALL(glBindFramebuffer(GL_FRAMEBUFFER, 0));
            if (m_resolve_rb)
            {
                GL_CALL(glBindFramebuffer(GL_READ_FRAMEBUFFER, m_fb));
                GL_CALL(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_resolve_rb->m_fb));
                GL_CALL(glBlitFramebuffer(0, 0, Config()->Width(), Config()->Height(), 0, 0, Config()->Width(), Config()->Height(), GL_COLOR_BUFFER_BIT, GL_NEAREST));
            }
            if (m_prev_fb != m_fb)
            {
                GL_CALL(glBindFramebuffer(GL_FRAMEBUFFER, m_prev_fb));
            }
        }

        void GlFrameBuffer::AttachColorTarget(std::uint32_t index, ITexture2D* buffer)
        {
            GlTexture2D* impl = dynamic_cast<GlTexture2D*>(buffer);
            if (!impl)
                throw OpenGLInvalidValueException(L"Buffer is invalid");

            Bind();
            GL_CALL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, GL_TEXTURE_2D, impl->GetIndex(), 0));
            buffer->Bind();
            Check();
            Unbind();
        }

        void GlFrameBuffer::AttachColorTarget(size_t index, IRenderBuffer* b)
        {
            GlColorRenderBuffer* buffer = dynamic_cast<GlColorRenderBuffer*>(b);
            if (!buffer)
                throw OpenGLInvalidValueException(L"Color render buffer is invalid");
            Bind();
            buffer->Bind();
            GL_CALL(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + (GLenum)index, GL_RENDERBUFFER, buffer->Index()));
            Check();
            Unbind();
        }

        void GlFrameBuffer::AttachDepthTarget(ITexture2D* buffer)
        {
            GlTexture2D* impl = dynamic_cast<GlTexture2D*>(buffer);
            if (!impl)
                throw OpenGLInvalidValueException(L"Depth buffer is invalid");

            Bind();
            buffer->Bind();
            GL_CALL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, impl->GetIndex(), 0));
            Check();
            Unbind();
        }

        void GlFrameBuffer::AttachDepthTarget(IRenderBuffer* b)
        {
            GlDepthRenderBuffer* buffer = dynamic_cast<GlDepthRenderBuffer*>(b);
            if (!buffer)
                throw OpenGLInvalidValueException(L"Depth buffer is invalid");

            Bind();
            buffer->Bind();
            GL_CALL(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, buffer->Index()));
            Check();
            Unbind();
        }

        void GlFrameBuffer::AttachDepthTarget(ITexture2DArray *b, size_t index)
        {
            GlTexture2DArray* buffer = dynamic_cast<GlTexture2DArray*>(b);
            if (!buffer)
                throw OpenGLInvalidValueException(L"Invalid depth target");

            Bind();
            GL_CALL(glFramebufferTextureLayer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, (GLint)buffer->GetId(), 0, index));
            Check();
            Unbind();
        }

        void GlFrameBuffer::SetRenderTarget(FrameBufferTarget value)
        {
            Bind();
            GL_CALL(glDrawBuffer(Convert(value)));
            Unbind();
        }

        void GlFrameBuffer::SetViewport(int x, int y, int width, int height)
        {
            Bind();
            GL_CALL(glViewport(x, y, width, height));
            Unbind();
        }        

        void GlFrameBuffer::Check()
        {
            GL_CALL(GLenum result = glCheckFramebufferStatus( GL_DRAW_FRAMEBUFFER));
            if (result == GL_FRAMEBUFFER_COMPLETE)
                return;
            else if (result == GL_FRAMEBUFFER_UNDEFINED)
                throw OpenGLInvalidFramebuffer(L"GL_FRAMEBUFFER_UNDEFINED is returned if target is the default framebuffer, but the default framebuffer does not exist");
            else if (result == GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT)
                throw OpenGLInvalidFramebuffer(L"GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT is returned if any of the framebuffer attachment points are framebuffer incomplete");
            else if (result == GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT)
                throw OpenGLInvalidFramebuffer(L"GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT is returned if the framebuffer does not have at least one image attached to it");
            else if (result == GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER)
                throw OpenGLInvalidFramebuffer(L"GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER is returned if the value of GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE for any color attachment point(s) named by GL_DRAWBUFFERi");
            else if (result == GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER)
                throw OpenGLInvalidFramebuffer(L"GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER is returned if GL_READ_BUFFER is not GL_NONE and the value of GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE for the color attachment point named by GL_READ_BUFFER.");
            else if (result == GL_FRAMEBUFFER_UNSUPPORTED)
                throw OpenGLInvalidFramebuffer(L"GL_FRAMEBUFFER_UNSUPPORTED is returned if the combination of internal formats of the attached images violates an implementation-dependent set of restrictions.");
            else if (result == GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE)
                throw OpenGLInvalidFramebuffer(L"GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE is returned if the value of GL_RENDERBUFFER_SAMPLES is not the same for all attached renderbuffers; if the value of GL_TEXTURE_SAMPLES is the not same for all attached textures; or, if the attached images are a Mix of renderbuffers and textures, the value of GL_RENDERBUFFER_SAMPLES does not match the value of GL_TEXTURE_SAMPLES.");
            else if (result == GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE)
                throw OpenGLInvalidFramebuffer(L"GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE is also returned if the value of GL_TEXTURE_FIXED_SAMPLE_LOCATIONS is not the same for all attached textures; or, if the attached images are a Mix of renderbuffers and textures, the value of GL_TEXTURE_FIXED_SAMPLE_LOCATIONS is not GL_TRUE for all attached textures.");
            else if (result == GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS)
                throw OpenGLInvalidFramebuffer(L"GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS is returned if any framebuffer attachment is layered, and any populated attachment is not layered, or if all populated color attachments are not from textures of the same target.");
            else
                throw OpenGLInvalidFramebuffer(L"Fuck");
        }

        void GlFrameBuffer::SetPolygonOffset(float a, float b)
        {
            GL_CALL(glPolygonOffset(a, b));
            if (a == 0 && b == 0)
            {
                GL_CALL(glDisable(GL_POLYGON_OFFSET_FILL));
            }
            else
            {
                GL_CALL(glEnable(GL_POLYGON_OFFSET_FILL));
            }
        }
    }

    extern PUNK_ENGINE_API IFrameBufferUniquePtr CreateFrameBuffer(IVideoDriver* driver) {
        IFrameBufferUniquePtr buffer{ new OpenGL::GlFrameBuffer(driver), DestroyFrameBuffer};
        return buffer;
    }

    extern PUNK_ENGINE_API IFrameBufferUniquePtr CreateFrameBuffer(int width, int height, IVideoDriver* driver)
    {
        auto fb = driver->GetSettings()->GetFrameBufferConfig(0);
        fb.Width(width);
        fb.Height(height);
        auto buffer = CreateFrameBuffer(driver);
        buffer->Config(fb);
        return buffer;
    }

    extern PUNK_ENGINE_API IFrameBufferUniquePtr CreateFrameBuffer(int width, int height, ImageModule::ImageFormat color_format, ImageModule::ImageFormat depth_format, IVideoDriver* driver)
    {
        auto fb = driver->GetSettings()->GetFrameBufferConfig(0);
        fb.Width(width);
        fb.Height(height);
        fb.ColorFormat(color_format);
        fb.DepthFormat(depth_format);
        auto buffer = CreateFrameBuffer(driver);
        buffer->Config(fb);
        return buffer;
    }

    extern PUNK_ENGINE_API IFrameBufferUniquePtr CreateFrameBuffer(int width, int height, ImageModule::ImageFormat color_format, ImageModule::ImageFormat depth_format, int depth_samples, IVideoDriver* driver)
    {
        auto fb = driver->GetSettings()->GetFrameBufferConfig(0);
        fb.Width(width);
        fb.Height(height);
        fb.ColorFormat(color_format);
        fb.DepthFormat(depth_format);
        fb.DepthSamples(depth_samples);
        auto buffer = CreateFrameBuffer(driver);
        buffer->Config(fb);
        return buffer;
    }

    extern PUNK_ENGINE_API IFrameBufferUniquePtr CreateFrameBuffer(int width, int height, ImageModule::ImageFormat color_format, ImageModule::ImageFormat depth_format, int depth_samples, int coverage_samples, IVideoDriver* driver)
    {
        auto fb = driver->GetSettings()->GetFrameBufferConfig(0);
        fb.Width(width);
        fb.Height(height);
        fb.ColorFormat(color_format);
        fb.DepthFormat(depth_format);
        fb.DepthSamples(depth_samples);
        fb.CoverageSamples(coverage_samples);
        auto buffer = CreateFrameBuffer(driver);
        buffer->Config(fb);
        return buffer;
    }

    extern PUNK_ENGINE_API IFrameBuffer* GetBackbuffer() {
        return &OpenGL::GlFrameBuffer::Backbuffer;
    }

    extern PUNK_ENGINE_API void DestroyFrameBuffer(IFrameBuffer* buffer) {
        OpenGL::GlFrameBuffer* fb = dynamic_cast<OpenGL::GlFrameBuffer*>(buffer);
        delete fb;
    }
}
PUNK_ENGINE_END
