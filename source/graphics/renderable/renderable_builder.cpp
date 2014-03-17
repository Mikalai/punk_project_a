#include <memory>
#include <graphics/primitives/module.h>
#include <graphics/error/module.h>
#include <math/vec3.h>
#include <math/vec2.h>
#include <math/bounding_sphere.h>
#include "renderable_builder.h"

PUNK_ENGINE_BEGIN
namespace Graphics
{
    RenderableBuilder::RenderableBuilder(IVideoDriver* driver)
		: m_driver(driver)
		, m_begin_active(false)
	{}

    RenderableBuilder::~RenderableBuilder() {
        if (m_bsphere) {
            delete m_bsphere;
            m_bsphere = nullptr;
        }
    }

    void RenderableBuilder::Vertex3f(float x, float y, float z)
	{
		ValidateDraw();
		m_vertex.push_back(Math::vec4(x, y, z, 1));
	}

    void RenderableBuilder::Vertex3fv(const float* value)
	{
		ValidateDraw();
		m_vertex.push_back(Math::vec4(value[0], value[1], value[2], 1));
	}

    void RenderableBuilder::Vertex3fv(const Math::vec3 &value)
	{
		ValidateDraw();
		m_vertex.push_back(Math::vec4(value[0], value[1], value[2], 1));
	}

    void RenderableBuilder::Color3f(float r, float g, float b)
	{
		ValidateDraw();
		m_color.push_back(Math::vec4(r, g, b, 1.0f));
	}

    void RenderableBuilder::Color3fv(const float* value)
	{
		ValidateDraw();
		m_color.push_back(Math::vec4(value[0], value[1], value[2], 1));
	}

    void RenderableBuilder::Color3fv(const Math::vec3& value)
	{
		ValidateDraw();
		m_color.push_back(Math::vec4(value, 1));
	}

    void RenderableBuilder::TexCoord2f(float x, float y)
	{
		ValidateDraw();
		m_texcoord.push_back(Math::vec4(x, y, 0, 0));
	}

    void RenderableBuilder::TexCoord2fv(const float* value)
	{
		ValidateDraw();
		m_texcoord.push_back(Math::vec4(value[0], value[1], 0, 0));
	}

    void RenderableBuilder::TexCoord2fv(const Math::vec2& value)
	{
		ValidateDraw();
		m_texcoord.push_back(Math::vec4(value[0], value[1], 0, 0));
	}

    void RenderableBuilder::Normal3f(float x, float y, float z)
	{
		ValidateDraw();
		m_normal.push_back(Math::vec4(x, y, z, 0));
	}

    void RenderableBuilder::Normal3fv(const float* value)
	{
		ValidateDraw();
		m_normal.push_back(Math::vec4(value[0], value[1], value[2], 0));
	}

    void RenderableBuilder::Normal3fv(const Math::vec3& value)
	{
		ValidateDraw();
		m_normal.push_back(Math::vec4(value[0], value[1], value[2], 0));
	}    

    void RenderableBuilder::ValidateBegin()
	{
		if (m_begin_active)
            throw Error::GraphicsException(L"Begin has been already called");
		m_begin_active = true;
	}

    void RenderableBuilder::ValidateEnd()
	{
		if (!m_begin_active)
            throw Error::GraphicsException(L"Failed to perform End(), because begin was not called");
		m_begin_active = false;
	}

    void RenderableBuilder::ValidateDraw()
	{
		if (!m_begin_active)
            throw Error::GraphicsException(L"Failed to draw, because Begin() was not called");
	}

    const Math::BoundingSphere* RenderableBuilder::GetBoundingSphere() const
    {
        if (m_bsphere)
            delete m_bsphere;
        std::unique_ptr<Math::BoundingSphere> s{new Math::BoundingSphere()};

        std::vector<Math::vec3> p(m_vertex.size());
        for (auto i = 0u; i != m_vertex.size(); ++i)
        {
            p[i] = m_vertex[i].XYZ();
        }
        s->Create(&p[0], p.size());
        return (m_bsphere = s.release());
    }

    bool RenderableBuilder::IsValid() const
    {
        return !m_vertex.empty();
    }

    extern "C" PUNK_ENGINE_API IRenderableBuilderUniquePtr CreateRenderableBuilder(IVideoDriver* driver) {
        IRenderableBuilderUniquePtr result{new RenderableBuilder(driver), DestroyRenderableBuilder};
        return result;
    }

    extern "C" PUNK_ENGINE_API void DestroyRenderableBuilder(IRenderableBuilder* value) {
        RenderableBuilder* o = dynamic_cast<RenderableBuilder*>(value);
        delete o;
    }

}
PUNK_ENGINE_END
