#ifndef _H_IGEOMETRY
#define _H_IGEOMETRY

#include <config.h>
#include <memory>
#include <cstdint>
#include <vector>
#include <math/vec2.h>
#include <math/vec3.h>
#include <math/vec4.h>
#include "icomponent_bone_weight.h"
#include "icomponent_color.h"
#include "icomponent_normal.h"
#include "icomponent_position.h"
#include "icomponent_texture.h"
#include "icomponent_index.h"
#include "icomponent_texture_face.h"

PUNK_ENGINE_BEGIN
namespace Graphics {
	class IVertexArray;
	class IIndexArray;
}
namespace Math {
	class BoundingBox;
	class BoundingSphere;
}
namespace Attributes {

	class IGeometry 
		: public IPositionComponent
		, public INormalComponent
		, public IColorComponent
		, public ITextureComponent
		, public IBoneWeightComponent
		, public IIndexComponent
		, public ITextureFaceComponent
	{
	public:
		virtual bool IsIndexed() const = 0;
		virtual bool Validate() = 0;
		virtual const Math::BoundingBox* GetBoundingBox() const = 0;
		virtual const Math::BoundingSphere* GetBoundingSphere() const = 0;
		virtual std::uint32_t GetVertexCount() = 0;		
	};

	using IGeometryUniquePtr = std::unique_ptr < IGeometry, void(*)(IGeometry*) > ;	
	extern PUNK_ENGINE_API IGeometryUniquePtr CreateGeometry();	
	extern PUNK_ENGINE_API void DestroyGeometry(IGeometry* value);
}
PUNK_ENGINE_END

#endif	//	_H_IGEOMETRY