#ifndef _H_IGEOMETRY
#define _H_IGEOMETRY

#include <config.h>
#include <memory>
#include <cstdint>
#include <vector>
#include <core/iobject.h>
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

	DEFINE_PUNK_GUID(IID_IGeometry, "3B04856F-622F-4AAD-984D-0A0FA5C34B27");

	class IGeometry 
		: public virtual Core::IObject
		, public IPositionComponent
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
		virtual void SetName(const Core::String& name) = 0;
		virtual const Core::String& GetName() const = 0;
	};

	using IGeometryUniquePtr = std::unique_ptr < IGeometry, void(*)(IGeometry*) > ;	
	extern PUNK_ENGINE_API IGeometryUniquePtr CreateGeometry();	
	extern PUNK_ENGINE_API void DestroyGeometry(IGeometry* value);
}
PUNK_ENGINE_END

#endif	//	_H_IGEOMETRY