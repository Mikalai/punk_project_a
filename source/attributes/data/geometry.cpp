#include "geometry.h"

PUNK_ENGINE_BEGIN
namespace Attributes
{
    Core::Rtti Geometry::Type{"Attributes.Geometry",
                              typeid(Geometry).hash_code(),
        {&Core::Object::Type}};

    Geometry::Geometry()
    {}

	Geometry::~Geometry()
    {}

    Math::BoundingBox& Geometry::GetBoundingBox()
    {
        return m_bbox;
    }

    const Math::BoundingBox& Geometry::GetBoundingBox() const
    {
        return m_bbox;
    }

    Math::BoundingSphere& Geometry::GetBoundingSphere()
    {
        return m_sphere;
    }

    const Math::BoundingSphere& Geometry::GetBoundingSphere() const
    {
        return m_sphere;
    }

//	void Geometry::DropGPUCache()
//	{
//		delete m_cache.m_gpu_buffer;
//		m_cache.m_gpu_buffer = nullptr;
//	}

//	bool Geometry::IsGPUCacheValid()
//	{
//		return m_cache.m_gpu_buffer != nullptr;
//	}

//	void Geometry::SetGPUBufferCache(Graphics::Renderable* value)
//	{
//		m_cache.m_gpu_buffer = value;
//	}

//	Graphics::Renderable* Geometry::GetGPUBufferCache()
//	{
//		return m_cache.m_gpu_buffer;
//	}

//	void Geometry::DropPhysicsCache()
//	{
//		delete m_cache.m_physics_buffer;
//	}

//	bool Geometry::IsPhysicsCacheValid()
//	{
//		return m_cache.m_physics_buffer != nullptr;
//	}

//	void Geometry::SetPhysicsCache(Core::Object* value)
//	{
//		m_cache.m_physics_buffer = value;
//	}

//	Core::Object* Geometry::GetPhysicsCache()
//	{
//		return m_cache.m_physics_buffer;
//	}
}
PUNK_ENGINE_END
