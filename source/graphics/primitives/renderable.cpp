#include <graphics/error/module.h>
#include "renderable.h"

PUNK_ENGINE_BEGIN
namespace Graphics
{
	Renderable::Renderable() 
	{}

    Renderable::~Renderable() {}

    void Renderable::Bind(std::int64_t)
    {
        throw Error::GraphicsException(L"Bind() not implemented");
    }

    void Renderable::Unbind()
    {
        throw Error::GraphicsException(L"Unbind() not implemented");
    }

    void Renderable::Render()
    {
        throw Error::GraphicsException(L"Load() not implemented");
    }

    std::uint64_t Renderable::GetMemoryUsage()
    {
        throw Error::GraphicsException(L"GetMemoryUsage() not implemented");
    }

    bool Renderable::HasData() const
    {
		throw Error::GraphicsException(L"HasData() not implemented");
	}

	extern PUNK_ENGINE_API void DestroyRenderable(IRenderable* value) {
		Renderable* r = dynamic_cast<Renderable*>(value);
		delete r;
	}

	//bool Renderable::Save(std::ostream& stream) const
	//{
	//	stream.write((char*)&m_primitive_type, sizeof(m_primitive_type));	//	it is always written but ignored by load function
	//	return true;
	//}

	//bool Renderable::Load(std::istream& stream)
	//{
	//	return true;	//	type is read by CreateFromStream
	//}

	//System::Proxy<Renderable> Renderable::CreateFromFile(const Core::String& path)
	//{
	//	std::ifstream stream(path.Data(), std::ios::binary);
	//	if (!stream.is_open())
	//		throw OpenGLException(L"Can't open file " + path);
	//	return CreateFromStream(stream);
	//}

	//System::Proxy<Renderable> Renderable::CreateFromStream(std::istream& stream)
	//{
	//	/*PrimitiveTypes type;
	//	stream.read((char*)&type, sizeof(type));

	//	switch (type)
	//	{
	//	case OpenGL::QUAD:
	//	return QuadObject::CreateFromStream(stream);
	//	case OpenGL::SKIN_MESH:
	//	return SkinMesh::CreateFromStream(stream);
	//	case OpenGL::STATIC_MESH:
	//	return StaticMesh::CreateFromStream(stream);
	//	default:
	//	throw OpenGLException(L"Can't create renderable from stream ");
	//	}
	//	return System::Proxy<Renderable>(nullptr);*/
	//	throw OpenGLException(L"Not implementerd");
	//}
}
PUNK_ENGINE_END
